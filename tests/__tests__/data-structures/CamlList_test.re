open TestFramework;
open Rhythm;

describe("CamlList", ({describe, test}) => {
  module FeatureFrontImmutableTests = FeatureFrontImmutableTests.Add(CamlList);
  FeatureFrontImmutableTests.register(describe);

  module FeatureBackTests = FeatureBackTests.Add(CamlList);
  FeatureBackTests.register(describe);

  module FeatureIndexedTests = FeatureIndexedTests.Add(CamlList);
  FeatureIndexedTests.register(describe);

  module FeatureSyntaxTests = FeatureSyntaxTests.Add(CamlList);
  FeatureSyntaxTests.register(describe);

  test("make", ({expect}) => {
    let list = CamlList.make();
    expect.int(CamlList.length(list)).toBe(0);
    expect.bool(CamlList.isEmpty(list)).toBeTrue();
  });

  test("init", ({expect}) => {
    let list = CamlList.init(5, i => i);
    expect.int(CamlList.length(list)).toBe(5);
    expect.bool(CamlList.isEmpty(list)).toBeFalse();
    expect.int(CamlList.getFirstExn(list)).toBe(0);
    expect.int(CamlList.getLastExn(list)).toBe(4);
  });
});
