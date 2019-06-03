module type QueryConfig = {
  let query: string;
  type t;
  let parse: Js.Json.t => t;
};

module type GraphQLClientBase = {
  let graphQLUrl: string;
  module Query: QueryConfig;
};

let makeQueryBody = (~maybeVariables=None, ~maybeOperationName=None, query) => {
  Js.Dict.fromList(
    List.concatMany([|
      [("query", Js.Json.string(query))],
      Option.mapWithDefault(maybeVariables, [], variables =>
        [("variables", variables)]
      ),
      Option.mapWithDefault(maybeOperationName, [], operationName =>
        [("operationName", Js.Json.string(operationName))]
      ),
    |]),
  )
  |> Js.Json.object_
  |> Js.Json.stringify;
};

type responseJson = {
  data: option(Js.Json.t),
  errors: option(list(Js.Json.t)),
};

let rawJson = json => json;
let parseResponseJson = json => {
  Json.Decode.{
    data:
      (json |> optional(field("data", nullable(rawJson))))
      ->(Option.flatMap(Js.Null.toOption)),
    errors:
      (json |> optional(field("errors", array(rawJson))))
      ->(Option.map(List.fromArray)),
  };
};

module MakeQuery = (T: GraphQLClientBase) => {
  let makeClient = (maybeVariables, maybeOperationName) =>
    Bs_fetch.(
      fetchWithInit(
        T.graphQLUrl,
        RequestInit.make(
          ~method_=Post,
          ~body=
            makeQueryBody(~maybeVariables, ~maybeOperationName, T.Query.query)
            |> BodyInit.make,
          ~headers=
            HeadersInit.makeWithArray([|
              ("content-type", "application/json"),
            |]),
          (),
        ),
      )
    );

  type reasonResponse = [
    | `Data(T.Query.t)
    | `DataWithError(T.Query.t, list(string))
    | `Error(list(string))
  ];

  let parse = json => {
    let response = parseResponseJson(json);

    (
      switch (response.data, response.errors) {
      | (Some(data), Some(errors)) =>
        `DataWithError((T.Query.parse(data), errors))
      | (Some(data), None) => `Data(T.Query.parse(data))
      | (None, Some(errors)) => `Error(errors)
      | (None, None) => `Error([Js.Json.string("No data")])
      }
    )
    ->Js.Promise.resolve;
  };

  let query = (~variables=?, ~operationName=?, ()) => {
    makeClient(variables, operationName)
    |> Js.Promise.then_(Bs_fetch.Response.json)
    |> Js.Promise.then_(parse);
  };
};
