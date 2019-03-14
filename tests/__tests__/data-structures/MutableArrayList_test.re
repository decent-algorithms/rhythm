open TestFramework;
open Rhythm;

describe("MutableArrayList", ({describe, test, testSkip}) => {
  module FeatureFrontTests = FeatureFrontTests.Add(MutableArrayList);
  FeatureFrontTests.register(describe);

  module FeatureBackTests = FeatureBackTests.Add(MutableArrayList);
  FeatureBackTests.register(describe);

  module FeatureIndexedTests = FeatureIndexedTests.Add(MutableArrayList);
  FeatureIndexedTests.register(describe);
});
