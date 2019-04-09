# todo list

- Convert the "main" manual functions to features as well for consistent docs
- Add Performance tests
- Convert all features to common/immutable/mutable
- DS.update needs to move to MutableIndexed feature. CamlArray is not dynamic
  sized so needs to use FrontImmutable, but the update function mutates array
  so needs to have update be mutable. So update has to move out of
  FrontImmutable (or some other solution be devised)
- Add zip, unzip, map, map2, map3 to sequence
- Add Option.map2, map3, etc
- Add Result module, similar to Option
- Remove and discourage Options/Result infix functions (hard for new people)
