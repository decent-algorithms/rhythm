open TestFramework;
open Rhythm;

describe("SimpleList", ({test}) => {
  test("make", ({expect}) => {
    let list = SimpleList.make();
    expect.int(SimpleList.length(list)).toBe(0);
    expect.bool(SimpleList.isEmpty(list)).toBeTrue();
  });

  test("init", ({expect}) => {
    let list = SimpleList.init(5, i => i);
    expect.int(SimpleList.length(list)).toBe(5);
    expect.bool(SimpleList.isEmpty(list)).toBeFalse();
    expect.int(SimpleList.getFirstExn(list)).toBe(0);
    expect.int(SimpleList.getLastExn(list)).toBe(4);
  });

  test("Syntax", ({expect}) => {
    let list = [0, 1, 2, 3, 4];
    /* This is an error, because an Array syntax has not been opened. */
    /* let one = list[1]; */
    let _ = list;
    /*
     * A standard, safe syntax for accessing into an array.
     */
    open SimpleList.Syntax;
    let list = [0, 1, 2, 3, 4];
    let one = list[1] |> Option.getExn;
    expect.int(one).toBe(1);
    /*
     * The nested syntax accepts an optional array as input so that deeply
     * nested arrays can still be easily accessed.
     */
    open SimpleList.SyntaxNested;
    let list = [0, 1, 2, 3, 4];
    let list = [list, list, list, list, list];
    let list = [list, list, list, list, list];
    let list = Some(list);
    let one = list[4][2][1] |> Option.getExn;
    expect.int(one).toBe(1);
    /*
     * This is the standard array syntax that is unsafe and can throw
     * exceptions when given invalid indices.
     */
    open SimpleList.SyntaxExn;
    let list = [0, 1, 2, 3, 4];
    let list = [list, list, list, list, list];
    let one = list[2][1];
    expect.int(one).toBe(1);
    /* When the index is too big an exception is thrown. */
    expect.fn(() => list[1000]).toThrow();
    /*
     * Because it may be recommended to open modules to enable syntax we
     * provide a module to reset syntax that was opened.
     */
    open SimpleList.SyntaxReset;
    let list = [0, 1, 2, 3, 4];
    /* This is an error, because we reset the Array syntax. */
    /* let one = list[1]; */
    let _ = list;
    ();
  });
});
