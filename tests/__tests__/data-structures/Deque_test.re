open TestFramework;
open Rhythm;

describe("Deque", ({describe, test}) => {
  module FeatureFrontImmutableTests = FeatureFrontImmutableTests.Add(Deque);
  FeatureFrontImmutableTests.register(describe);

  module FeatureBackTests = FeatureBackTests.Add(Deque);
  FeatureBackTests.register(describe);
});
