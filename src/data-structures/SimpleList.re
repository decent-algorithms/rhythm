include SimpleListCore;

include FeatureSyntax.Add({
  include SimpleListCore;
  let length = Caml.List.length;
  let get = Caml.List.nth;
});

include FeatureSequence.Add(SimpleListCore);

include FeatureFront.Add({
  include SimpleListCore;
  open FeatureFront;
  let fastGetFirst = GetFirstExn(SimpleListCore.getFirstExn);
  let fastAddFirst = AddFirst(SimpleListCore.addFirst);
  let fastRemoveFirst = RemoveFirstExn(SimpleListCore.removeFirstExn);
});

include FeatureBack.Add({
  include SimpleListCore;
  open FeatureBack;
  let fastGetLast = SlowGetLast;
  let fastAddLast = SlowAddLast;
  let fastRemoveLast = SlowRemoveLast;
});

let getIndex = (i, arr) => Syntax.(arr[i]);

let getIndexExn = (i, arr) => SyntaxExn.(arr[i]);
