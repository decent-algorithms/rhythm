open TestFramework;
open Rhythm;

describe("CamlArray", ({describe, test}) => {
  module FeatureFrontImmutableTests =
    FeatureFrontImmutableTests.Add(CamlArray);
  FeatureFrontImmutableTests.register(describe);

  module FeatureBackTests = FeatureBackTests.Add(CamlArray);
  FeatureBackTests.register(describe);

  module FeatureIndexedTests = FeatureIndexedTests.Add(CamlArray);
  FeatureIndexedTests.register(describe);

  module FeatureMutableIndexedTests =
    FeatureMutableIndexedTests.Add(CamlArray);
  FeatureMutableIndexedTests.register(describe);

  module FeatureMutableSyntaxTests = FeatureMutableSyntaxTests.Add(CamlArray);
  FeatureMutableSyntaxTests.register(describe);
});
