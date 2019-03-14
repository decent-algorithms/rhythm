open TestFramework;
open Rhythm;

describe("Deque", ({describe, test}) => {
  module FeatureBackTests = FeatureBackTests.Add(Deque);
  FeatureBackTests.register(describe);
});
