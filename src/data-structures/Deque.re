include DequeCore;

include FeatureSequence.Add({
  include FeatureSequence.DefaultConfig;
  include DequeCore;
  open FeatureSequence;
  let fastReverse = Reverse(DequeCore.reverse);
});

include FeatureFront.Add({
  include DequeCore;
  open FeatureFront;
  let fastGetFirst = GetFirstExn(DequeCore.getFirstExn);
  let fastAddFirst = AddFirst(DequeCore.addFirst);
  let fastRemoveFirst = RemoveFirstExn(DequeCore.removeFirstExn);
});

include FeatureBack.Add({
  include DequeCore;
  open FeatureBack;
  let fastGetLast = GetLastExn(DequeCore.getLastExn);
  let fastAddLast = AddLast(DequeCore.addLast);
  let fastRemoveLast = RemoveLastExn(DequeCore.removeLastExn);
});
