module BaseClient = (Query: GraphQLFetchClient.QueryConfig) => {
  let graphQLUrl = "https://graphql-pokemon.now.sh/";
  module Query = Query;
};

module GetPickachu = {
  module GraphQL = [%graphql
    {|
    {
      pokemon(name:"Pikachu") {
        id
        number
        name
        image
        evolutions {
          id
          number
          name
          image
        }
      }
    }
  |}
  ];

  module Query = GraphQLFetchClient.MakeQuery((BaseClient(GraphQL)));
};
