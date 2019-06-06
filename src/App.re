open Css;

Utils.cssReset();

[@react.component]
let make = () => {
  let (query, setQuery) = React.useState(() => "");
  let (pokemons, setPokemons) = React.useState(() => [||]);
  let (filterPokemons, setFilteredPokemons) = React.useState(() => [||]);
  let (favoritePokemons, setFavoritePokemons) = React.useState(() => [||]);
  let (showFavorites, toggleFavorites) = React.useState(() => false);

  let searchRef = React.useRef(Js.Nullable.null);
  React.useEffect0(() => {
    // get focus search
    searchRef
    ->React.Ref.current
    ->Js.Nullable.toOption
    ->(Option.map(r => ReactDOMRe.domElementToObj(r)##focus()))
    ->ignore;
    None;
  });

  React.useEffect1(
    () => {
      setFilteredPokemons(_ =>
        switch (String.length(query)) {
        | 0 => pokemons
        | _ =>
          pokemons->(
                      Belt.Array.keep(maybePokemon =>
                        Belt.Option.mapWithDefault(
                          maybePokemon, false, pokemon =>
                          Js.String.includes(
                            String.lowercase(query),
                            String.lowercase(
                              Belt.Option.getWithDefault(pokemon##name, ""),
                            ),
                          )
                        )
                      )
                    )
        }
      );
      None;
    },
    [|query|],
  );

  React.useEffect1(
    () => {
      showFavorites
        ? setFilteredPokemons(_ =>
            pokemons->(
                        Array.keep(maybePokemon =>
                          Belt.Option.mapWithDefault(
                            maybePokemon, false, pokemon =>
                            Belt.Array.some(favoritePokemons, fp =>
                              fp == pokemon##id
                            )
                          )
                        )
                      )
          )
        : setFilteredPokemons(_ => pokemons);
      None;
    },
    [|showFavorites|],
  );

  let favoriteKeyHandler = event => {
    Webapi.Dom.KeyboardEvent.key(event) == "f"
      ? toggleFavorites(oldFavorites => !oldFavorites) |> ignore : ();
  };

  React.useEffect0(() => {
    Webapi.Dom.Window.addKeyDownEventListener(
      favoriteKeyHandler,
      Webapi.Dom.window,
    );
    Some(
      _ =>
        Webapi.Dom.Window.removeKeyDownEventListener(
          favoriteKeyHandler,
          Webapi.Dom.window,
        ),
    );
  });

  React.useEffect0(() => {
    Pokedex.GetPokemons.Query.query()
    |> Js.Promise.then_(response =>
         (
           switch (response) {
           | `Data(data)
           | `DataWithError(data, _) =>
             Belt.Option.map(
               data##pokemons,
               pokemons => {
                 setFilteredPokemons(_ => pokemons);
                 setPokemons(_ => pokemons);
               },
             )
             ->ignore
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
      {React.string("ShowFavorites")}
      <input
        type_="checkbox"
        checked=showFavorites
        onChange={_event => toggleFavorites(oldState => !oldState)}
      />
    </div>
    <div>
      <input
        ref={ReactDOMRe.Ref.domRef(searchRef)}
        type_="text"
        placeholder="Search for pokemon"
        value=query
        onChange={event => {
          ReactEvent.Form.persist(event);
          setQuery(ReactEvent.Form.target(event)##value);
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
        /* TODO: Display PokemonDetails onClick */
        /* TODO: Display a list of Pokemon */
        /* TODO: Filter list of pokemon by search query */
        /* TODO: Focus on search box on page load */
        /* TODO: Mark pokemons as favorites */
        /* TODO: Filter favorite pokemons on 'f' key press */

          Belt.Array.map(filterPokemons, maybePokemon =>
            Option.mapWithDefault(
              maybePokemon,
              React.null,
              pokemon => {
                let isFavorite =
                  Belt.Array.some(favoritePokemons, fp => fp == pokemon##id);
                <Pokemon
                  key={pokemon##id}
                  pokemon
                  isFavorite
                  onClickFavorite={_ =>
                    setFavoritePokemons(favorites =>
                      isFavorite
                        ? Belt.Array.keep(favorites, fp => fp != pokemon##id)
                        : Belt.Array.concat(favorites, [|pokemon##id|])
                    )
                  }
                  onClick={_ =>
                    renderModal(
                      <button onClick={_ => closeModal()}>
                        {<PokemonDetails pokemon onClick={_ => closeModal()} />}
                      </button>,
                    )
                  }
                />;
              },
            )
          )
          ->React.array
        }
    </Modal>
    <div />
  </div>;
};