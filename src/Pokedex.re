module BaseClient = (Query: GraphQLFetchClient.QueryConfig) => {
  let graphQLUrl = "https://graphql-pokemon.now.sh/";
  module Query = Query;
};

module GetPokemons = {
  module GraphQL = [%graphql
    {|
    {
      pokemons(first: 151) {
        id
        number
        name
        image
        types
        evolutions {
          id
          number
          name
          image
          types
        }
      }
    }
  |}
  ];

  module Query = GraphQLFetchClient.MakeQuery((BaseClient(GraphQL)));
};
