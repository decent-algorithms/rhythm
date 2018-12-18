open TestFramework;

describe("Example Describe", ({test}) => {
  test("Example Test 1", ({expect}) => {
    expect.int(Rhythm.Example.value).toBe(1);
    expect.int(2).toBe(2);
  });

  test("Example Test 2", ({expect}) => {
    expect.int(Rhythm.Example.value).toBe(1);
    expect.int(2).toBe(2);
  });
});
