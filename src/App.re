open Css;

Utils.cssReset();

[@react.component]
let make = () => {
  let (pokemons: option(Pokedex.GetPokemons.GraphQL.t), setPokemons) =
    React.useState(() => None);

  let searchRef = React.useRef(Js.Nullable.null);
  React.useEffect0(() =>
    searchRef
    ->React.Ref.current
    ->Js.Nullable.toOption
    ->Option.map(myRef => ReactDOMRe.domElementToObj(myRef)##focus())
  );

  let (showFavorites, toggleFav) = React.useState(() => false);

  let faveKeyBoardHandler = event => {
    Webapi.Dom.KeyboardEvent.key(event) == "f"
      ? toggleFav(prevShowFavorites => !prevShowFavorites) |> ignore : ();
  };

  React.useEffect0(() => {
    Webapi.Dom.Window.addKeyDownEventListener(
      faveKeyBoardHandler,
      Webapi.Dom.window,
    );
    Some(
      _ =>
        Webapi.Dom.Window.removeKeyDownEventListener(
          faveKeyBoardHandler,
          Webapi.Dom.window,
        ),
    );
  });

  let (favorites, addFavorite) = React.useState(() => []);
  let (search, onSearchChange) = React.useState(() => "");
  
  React.useEffect0(() => {
    Pokedex.GetPokemons.Query.query()
    |> Js.Promise.then_(response =>
         (
           switch (response) {
           | `Data(data)
           | `DataWithError(data, _) => setPokemons(_ => Some(data))
           | `Error(_) => Js.log("Some error I guess :(")
           }
         )
         |> Js.Promise.resolve
       )
    |> ignore;
    None;
  });
  <div className={style([margin(px(16))])}>
    <div className={style([fontSize(px(24)), marginBottom(px(16))])}>
      {ReasonReact.string("Pokedex")}
    </div>
    <div>
      <input
        value=search
        type_="text"
        ref={ReactDOMRe.Ref.domRef(searchRef)}
        placeholder="Search for pokemon"
        onChange={event => {
          let e = event->ReactEvent.Form.target##value;
          Js.log(e);
          onSearchChange(e);
        }}
        className={style([
          width(pct(100.)),
          borderStyle(`none),
          borderBottom(px(1), `solid, lightgray),
          fontSize(px(16)),
          height(px(32)),
          marginBottom(px(16)),
          backgroundImage(
            `url(
              "data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHdpZHRoPSIyNCIgaGVpZ2h0PSIyNCIgdmlld0JveD0iMCAwIDI0IDI0Ij48cGF0aCBmaWxsPSJyZ2JhKDAsMCwwLDAuNCkiIGQ9Ik0xNS41IDE0aC0uNzlsLS4yOC0uMjdDMTUuNDEgMTIuNTkgMTYgMTEuMTEgMTYgOS41IDE2IDUuOTEgMTMuMDkgMyA5LjUgM1MzIDUuOTEgMyA5LjUgNS45MSAxNiA5LjUgMTZjMS42MSAwIDMuMDktLjU5IDQuMjMtMS41N2wuMjcuMjh2Ljc5bDUgNC45OUwyMC40OSAxOWwtNC45OS01em0tNiAwQzcuMDEgMTQgNSAxMS45OSA1IDkuNVM3LjAxIDUgOS41IDUgMTQgNy4wMSAxNCA5LjUgMTEuOTkgMTQgOS41IDE0eiIvPjwvc3ZnPg==",
            ),
          ),
          backgroundRepeat(`noRepeat),
          unsafe("background-position", "right center"),
        ])}
      />
    </div>
    <Modal>
      ...{(renderModal, closeModal) =>
          switch (pokemons) {
          | Some(data) =>
            switch (data##pokemons) {
            | Some(pokemons) =>
              let filteredPokemons =
                showFavorites
                  ? pokemons->Array.keep(maybePoke => {
                      let poke = maybePoke->Option.getExn;
                      let id = poke##id;
                      let matches = Belt.Array.some(Belt.List.toArray(favorites),
                        favId => favId == id
                      )

                      matches;
                    })
                  :
                Js.String.length(search) > 0
                  ? pokemons->Array.keep(maybePoke => {
                      let poke = maybePoke->Option.getExn;
                      let name = poke##name->Option.getExn;
                      let nameLower = Js.String.toLowerCase(name);
                      let matches = search->Js.String.includes(nameLower);

                      matches;
                    })
                  : pokemons;
              filteredPokemons
              ->Array.map(maybePoke => {
                  let poke = maybePoke->Option.getExn;
                  <Pokemon
                    onFave={event => {
                      ReactEvent.Mouse.stopPropagation(event);
                      let newFaves = [poke##id, ...favorites];
                      addFavorite(_ => newFaves);
                    }}
                    key=poke##id
                    pokemon=poke
                    onClick={_ =>
                      renderModal(
                        <PokemonDetails
                          pokemon=poke
                          onClick={_ => closeModal()}
                        />,
                      )
                    }
                  />;
                })
              ->React.array;
            | None => React.string("Not available")
            }
          | None => React.string("Not available")
          }
        }
    </Modal>
  </div>;
};