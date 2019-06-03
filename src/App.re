[@react.component]
let make = () => {
  React.useEffect0(() => {
    Pokedex.GetPickachu.Query.query()
    |> Js.Promise.then_(response => Js.log(response) |> Js.Promise.resolve);
    None;
  });
  <div> {ReasonReact.string("Hello world")} </div>;
};
