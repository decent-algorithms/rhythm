open TestFramework;
open Rhythm;

describe("MutableArrayList", ({describe, test}) => {
  module FeatureBackTests = FeatureBackTests.Add(MutableArrayList);
  FeatureBackTests.register(describe);
});
