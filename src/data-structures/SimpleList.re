include SimpleListCore;

include FeatureSyntax.Add({
  include SimpleListCore;
  let get = Caml.List.nth;
});

include FeatureSequence.Add({
  include FeatureSequence.DefaultConfig;
  include SimpleListCore;
});

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

include FeatureIndexed.Add({
  include SimpleListCore;
  let getIndexExn = (i, ds) => SyntaxExn.(ds[i]);
});
