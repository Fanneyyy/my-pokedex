open Css;

[@react.component]
let make = (~pokemon, ~onClick) =>
  <button
    className={style([
      width(pct(100.)),
      height(pct(100.)),
      margin(px(10)),
      hover([opacity(0.7), cursor(`pointer)]),
    ])}
    key={Option.getWithDefault(pokemon##name, "")}
    onClick>
    <div>
      {Option.mapWithDefault(pokemon##image, React.null, image =>
         <img
           className={style([height(px(600)), width(px(600))])}
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
          flexDirection(`column),
          background(hex("00000099")),
          color(white),
          fontSize(px(20)),
        ])}>
        {Option.mapWithDefault(pokemon##name, React.null, name =>
           <p> {React.string(name)} </p>
         )}
        {Option.mapWithDefault(pokemon##name, React.null, name =>
           <p> {React.string("Some more details...")} </p>
         )}
      </div>
    </div>
  </button>;
