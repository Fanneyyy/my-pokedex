open Css;

let cssReset = () => {
  global("html", [height(pct(100.))]);
  global(
    "body",
    [
      fontFamily("Roboto"),
      height(pct(100.)),
      margin(px(0)),
      background(hex("EEEEEE")),
    ],
  );

  global(
    "button",
    [
      unsafe("-webkit-appearance", "none"),
      borderWidth(`zero),
      background(`none),
      cursor(`pointer),
    ],
  );
};

[@bs.deriving jsConverter]
type types = [
  | `Psychic
  | `Dragon
  | `Flying
  | `Grass
  | `Poison
  | `Fire
  | `Water
  | `Bug
  | `Normal
  | `Electric
  | `Ground
  | `Fairy
  | `Fighting
  | `Rock
  | `Steel
  | `Ice
  | `Ghost
];

let getTypeColor = _type =>
  switch (_type) {
  | `Psychic => hex("F85888")
  | `Dragon => hex("7038F8")
  | `Flying => hex("A890F0")
  | `Grass => hex("8ac460")
  | `Poison => hex("A040A0")
  | `Fire => hex("F08030")
  | `Water => hex("6890F0")
  | `Bug => hex("A8B820")
  | `Normal => hex("A8A878")
  | `Electric => hex("F8D030")
  | `Ground => hex("E0C068")
  | `Fairy => hex("EE99AC")
  | `Fighting => hex("C03028")
  | `Rock => hex("B8A038")
  | `Steel => hex("B8B8D0")
  | `Ice => hex("98D8D8")
  | `Ghost => hex("705898")
  };

let getBackgroundColor = types =>
  switch (types) {
  | Some(types) when Array.length(types) == 2 =>
    style([
      background(
        linearGradient(
          deg(110),
          [
            (
              50,
              getTypeColor(
                Option.getExn(
                  typesFromJs(
                    Option.getWithDefault(Array.getExn(types, 0), "Grass"),
                  ),
                ),
              ),
            ),
            (
              50,
              getTypeColor(
                Option.getExn(
                  typesFromJs(
                    Option.getWithDefault(Array.getExn(types, 1), "Grass"),
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    ])
  | Some(types) when Array.length(types) == 1 =>
    style([
      background(
        getTypeColor(
          Option.getExn(
            typesFromJs(
              Option.getWithDefault(Array.getExn(types, 0), "Grass"),
            ),
          ),
        ),
      ),
    ])
  | _ => style([background(white)])
  };
