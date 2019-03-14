open TestFramework;
open Rhythm;

describe("Deque", ({describe, test}) => {
  module FeatureFrontTests = FeatureFrontTests.Add(Deque);
  FeatureFrontTests.register(describe);

  module FeatureBackTests = FeatureBackTests.Add(Deque);
  FeatureBackTests.register(describe);
});
