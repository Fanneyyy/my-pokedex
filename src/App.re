open Css;
[@react.component]
let make = () =>
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
              "data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zd…M3LjAxIDUgOS41IDUgMTQgNy4wMSAxNCA5LjUgMTEuOTkgMTQgOS41IDE0eiIvPjwvc3ZnPg==",
            ),
          ),
          backgroundRepeat(`noRepeat),
          unsafe("background-position", "right center"),
        ])}
      />
    </div>
    <div> {ReasonReact.string("List")} </div>
  </div>;