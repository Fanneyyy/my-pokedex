open Css;

[@react.component]
let make = (~pokemon, ~onFave, ~onClick) =>
  <button
    className={style([
      margin(px(10)),
      hover([opacity(0.7), cursor(`pointer)]),
    ])}
    key={Option.getWithDefault(pokemon##name, "")}
    onClick>
    <div>
      {Option.mapWithDefault(pokemon##image, React.null, image =>
         <img
           className={style([height(px(300)), width(px(300))])}
           src=image
         />
       )}
    </div>
    <div className={Utils.getBackgroundColor(pokemon##types)}>
      <div
        className={style([
          display(`flex),
          flexDirection(`row),
          justifyContent(`spaceEvenly),
        ])}>
        {Option.mapWithDefault(pokemon##types, React.null, types =>
           Array.map(types, _type =>
             Option.mapWithDefault(_type, React.null, _type =>
               <p key=_type> {React.string(_type)} </p>
             )
           )
           ->React.array
         )}
      </div>
      <div
        className={style([
          display(`flex),
          justifyContent(`center),
          background(hex("00000099")),
          color(white),
          fontSize(px(20)),
        ])}>
        {Option.mapWithDefault(pokemon##name, React.null, name =>
           <p> {React.string(name)} </p>
         )}
      </div>
      <button onClick=onFave> {ReasonReact.string("Fav this poke!")} </button>
    </div>
  </button>;