open Css;

[@react.component]
let make = (~children) => {
  let (modal, setModal) = React.useState(() => None);

  <>
    {children(modal => setModal(_ => Some(modal)), () => setModal(_ => None))}
    {switch (modal) {
     | None => React.null
     | Some(modal) =>
       <div
         className={style([
           position(`fixed),
           top(px(0)),
           bottom(px(0)),
           right(px(0)),
           left(px(0)),
           width(pct(100.)),
           height(pct(100.)),
           zIndex(10),
           overflowY(`scroll),
           background(hex("FFFFFF")),
           opacity(0.0),
           animationDuration(150),
           animationFillMode(`forwards),
           animationDirection(`normal),
           animationTimingFunction(cubicBesier(0.08, 0.95, 0.67, 0.97)),
           animationName(
             keyframes([
               (0, [transform(translateY(px(120))), opacity(0.0)]),
               (100, [transform(translateY(px(0))), opacity(1.0)]),
             ]),
           ),
         ])}>
         <div
           className={style([
             height(`calc((`sub, pct(100.), px(32)))),
             padding(px(16)),
           ])}>
           modal
         </div>
       </div>
     }}
  </>;
};
