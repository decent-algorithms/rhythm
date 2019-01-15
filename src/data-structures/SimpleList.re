include SimpleListCore;

include FeatureSyntax.Add({
  include SimpleListCore;
  let get = Caml.List.nth;
});

include FeatureSequence.Add({
  open FeatureSequence;
  include Default;
  include SimpleListCore;
});

include FeatureFront.Add({
  open FeatureFront;
  include Default;
  include SimpleListCore;
  let fastGetFirst = GetFirstExn(SimpleListCore.getFirstExn);
  let fastAddFirst = AddFirst(SimpleListCore.addFirst);
  let fastRemoveFirst = RemoveFirstExn(SimpleListCore.removeFirstExn);
});

include FeatureBack.Add({
  open FeatureBack;
  include Default;
  include SimpleListCore;
});

include FeatureIndexed.Add({
  include SimpleListCore;
  let getIndexExn = (i, ds) => SyntaxExn.(ds[i]);
});
