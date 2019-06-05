open Css;

Utils.cssReset();

[@react.component]
let make = () => {
  React.useEffect0(() => {
    Pokedex.GetPokemons.Query.query()
    |> Js.Promise.then_(response =>
         (
           switch (response) {
           | `Data(data)
           | `DataWithError(data, _) => Js.log(data) /* TODO: Store response */
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
        type_="text"
        placeholder="Search for pokemon"
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
        /* TODO: Start a timer onClick that closes the modal after 5 seconds */
        /* TODO: Display PokemonDetails onClick */
        /* TODO: Display a list of Pokemon */

          <button
            onClick={_ =>
              renderModal(
                <button onClick={_ => closeModal()}>
                  {React.string("Modal")}
                </button>,
              )
            }>
            {ReasonReact.string("List")}
          </button>
        }
    </Modal>
  </div>;
};
