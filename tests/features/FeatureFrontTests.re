open Rhythm;

module type DS = {
  type t('el);
  let toCamlList: t('el) => list('el);
  let fromCamlList: list('el) => t('el);
  include FeatureFront.Interface with type tFront('el) = t('el);
};

module type Output = {let register: Rely.Describe.describeFn(_) => unit;};

module Add = (DS: DS) : Output => {
  open Rely.Describe;
  let register = describe =>
    describe("FeatureFront", ({test}) => {
      test("Basic usage", ({expect}) => {
        let ds = DS.fromCamlList([]);
        expect.fn(() => DS.getFirstExn(ds)).toThrow();
        let ds = DS.addFirst(1, ds);
        expect.int(DS.getFirstExn(ds)).toBe(1);
        let ds = DS.addFirst(2, ds);
        expect.int(DS.getFirstExn(ds)).toBe(2);
        let ds = DS.addFirst(3, ds);
        expect.int(DS.getFirstExn(ds)).toBe(3);
        let ds = DS.addFirst(4, ds);
        expect.int(DS.getFirstExn(ds)).toBe(4);
        let ds = DS.removeFirstExn(ds);
        expect.int(DS.getFirstExn(ds)).toBe(3);
        let ds = DS.removeFirstExn(ds);
        expect.int(DS.getFirstExn(ds)).toBe(2);
        let ds = DS.removeFirstExn(ds);
        expect.int(DS.getFirstExn(ds)).toBe(1);
      });

      test("getFirst", ({expect}) => {
        let none = (-1);
        let getFirst = list =>
          list
          |> DS.fromCamlList
          |> DS.getFirst
          |> Option.getWithDefault(none);
        /* Examples */
        expect.int(getFirst([1, 2, 3, 4])).toBe(1);
        expect.int(getFirst([])).toBe(none);
        /* Additional tests */
        expect.int(getFirst([1])).toBe(1);
      });

      test("getFirstExn", ({expect}) => {
        let getFirstExn = list => list |> DS.fromCamlList |> DS.getFirstExn;
        /* Examples */
        expect.int(getFirstExn([1, 2, 3, 4])).toBe(1);
        expect.fn(() => getFirstExn([])).toThrow();
        /* Additional tests */
        expect.int(getFirstExn([1])).toBe(1);
      });

      test("getFirstN", ({expect}) => {
        let none = [(-1)];
        let getFirstN = (n, list) =>
          list
          |> DS.fromCamlList
          |> DS.getFirstN(n)
          |> Option.getWithDefault(DS.fromCamlList(none))
          |> DS.toCamlList;
        /* Examples */
        expect.list(getFirstN(2, [1, 2, 3, 4])).toEqual([1, 2]);
        expect.list(getFirstN(1, [1, 2, 3, 4])).toEqual([1]);
        expect.list(getFirstN(0, [])).toEqual([]);
        expect.list(getFirstN(1000, [1, 2])).toEqual(none);
        expect.list(getFirstN(1, [])).toEqual(none);
      });

      test("getFirstNExn", ({expect}) => {
        let getFirstNExn = (n, list) =>
          list |> DS.fromCamlList |> DS.getFirstNExn(n) |> DS.toCamlList;
        /* Examples */
        expect.list(getFirstNExn(2, [1, 2, 3, 4])).toEqual([1, 2]);
        expect.list(getFirstNExn(1, [1, 2, 3, 4])).toEqual([1]);
        expect.list(getFirstNExn(0, [])).toEqual([]);
        expect.fn(() => getFirstNExn(1000, [1, 2])).toThrow();
        expect.fn(() => getFirstNExn(1, [])).toThrow();
      });

      test("addFirst", ({expect}) => {
        let addFirst = (el, list) =>
          list |> DS.fromCamlList |> DS.addFirst(el) |> DS.toCamlList;
        /* Examples */
        expect.list(addFirst(9, [1, 2, 3])).toEqual([9, 1, 2, 3]);
        expect.list(addFirst(9, [])).toEqual([9]);
      });

      test("removeFirst", ({expect}) => {
        let none = [(-1)];
        let removeFirst = list =>
          list
          |> DS.fromCamlList
          |> DS.removeFirst
          |> Option.getWithDefault(DS.fromCamlList(none))
          |> DS.toCamlList;
        /* Examples */
        expect.list(removeFirst([1, 2, 3])).toEqual([2, 3]);
        expect.list(removeFirst([])).toEqual(none);
      });

      test("removeFirstExn", ({expect}) => {
        let removeFirstExn = list =>
          list |> DS.fromCamlList |> DS.removeFirstExn |> DS.toCamlList;
        /* Examples */
        expect.list(removeFirstExn([1, 2, 3])).toEqual([2, 3]);
        expect.fn(() => removeFirstExn([])).toThrow();
      });

      test("removeFirstN", ({expect}) => {
        let none = [(-1)];
        let removeFirstN = (n, list) =>
          list
          |> DS.fromCamlList
          |> DS.removeFirstN(n)
          |> Option.getWithDefault(DS.fromCamlList(none))
          |> DS.toCamlList;
        /* Examples */
        expect.list(removeFirstN(1, [1, 2, 3])).toEqual([2, 3]);
        expect.list(removeFirstN(2, [1, 2, 3])).toEqual([3]);
        expect.list(removeFirstN(0, [])).toEqual([]);
        expect.list(removeFirstN(1000, [1, 2, 3])).toEqual(none);
        expect.list(removeFirstN(1, [])).toEqual(none);
      });

      test("removeFirstNExn", ({expect}) => {
        let removeFirstNExn = (n, list) =>
          list |> DS.fromCamlList |> DS.removeFirstNExn(n) |> DS.toCamlList;
        /* Examples */
        expect.list(removeFirstNExn(1, [1, 2, 3])).toEqual([2, 3]);
        expect.list(removeFirstNExn(2, [1, 2, 3])).toEqual([3]);
        expect.list(removeFirstNExn(0, [])).toEqual([]);
        expect.fn(() => removeFirstNExn(1000, [1, 2, 3])).toThrow();
        expect.fn(() => removeFirstNExn(1, [])).toThrow();
      });

      test("updateFirst", ({expect}) => {
        let none = [(-1)];
        let updateFirst = (fn, list) =>
          list
          |> DS.fromCamlList
          |> DS.updateFirst(fn)
          |> Option.getWithDefault(DS.fromCamlList(none))
          |> DS.toCamlList;
        /* Examples */
        expect.list(updateFirst(x => x + 1, [1, 2, 3])).toEqual([2, 2, 3]);
        expect.list(updateFirst(x => x + 1, [])).toEqual(none);
      });

      test("updateFirstExn", ({expect}) => {
        let updateFirstExn = (fn, list) =>
          list |> DS.fromCamlList |> DS.updateFirstExn(fn) |> DS.toCamlList;
        /* Examples */
        expect.list(updateFirstExn(x => x + 1, [1, 2, 3])).toEqual([
          2,
          2,
          3,
        ]);
        expect.fn(() => updateFirstExn(x => x + 1, [])).toThrow();
      });
    });
};
