open Rhythm;

module type DS = {
  type t('el);
  let toCamlList: t('el) => list('el);
  let fromCamlList: list('el) => t('el);
  include
    FeatureFrontMutable.Interface with type tFrontMutable('el) = t('el);
};

module type Output = {let register: Rely.Describe.describeFn(_) => unit;};

module Add = (DS: DS) : Output => {
  open Rely.Describe;

  type setup('el) = {
    innerDS: ref(DS.t('el)),
    toList: unit => CamlListCore.t('el),
    reset: CamlListCore.t('el) => DS.t('el),
  };

  let setup = () => {
    let innerDS = ref(DS.fromCamlList([]));
    let toList = () => DS.toCamlList(innerDS.contents);
    let reset = (list) => {
      innerDS.contents = DS.fromCamlList(list);
      innerDS.contents;
    };
    {innerDS, toList, reset};
  };

  let register = describe => {
    module FeatureFrontCommonTests = FeatureFrontCommonTests.Add(DS);
    FeatureFrontCommonTests.register(describe);

    describe("FeatureFrontMutable", ({test}) => {
      test("Basic usage", ({expect}) => {
        let {toList, reset} = setup();
        let ds = reset([]);

        expect.fn(() => DS.getFirstExn(ds)).toThrow();

        let _ = DS.addFirst(1, ds);
        expect.list(toList()).toEqual([1]);

        let _ = DS.addFirst(2, ds);
        expect.list(toList()).toEqual([2, 1]);

        let _ = DS.addFirst(3, ds);
        expect.list(toList()).toEqual([3, 2, 1]);

        let _ = DS.addFirst(4, ds);
        expect.list(toList()).toEqual([4, 3, 2, 1]);

        let _ = DS.removeFirstExn(ds);
        expect.list(toList()).toEqual([3, 2, 1]);

        let _ = DS.removeFirstExn(ds);
        expect.list(toList()).toEqual([2, 1]);

        let _ = DS.removeFirstExn(ds);
        expect.list(toList()).toEqual([1]);
      });

      test("addFirst", ({expect}) => {
        let {toList, reset} = setup();

        let ds = reset([1, 2, 3]);
        let _ = DS.addFirst(9, ds);
        expect.list(toList()).toEqual([9, 1, 2, 3]);

        let ds = reset([]);
        let _ = DS.addFirst(9, ds);
        expect.list(DS.toCamlList(ds)).toEqual([9]);
      });

      test("removeFirst", ({expect}) => {
        let {toList, reset} = setup();

        let ds = reset([1, 2, 3]);
        let _ = DS.removeFirst(ds);
        expect.list(toList()).toEqual([2, 3]);

        let ds = reset([1, 2, 3])
        let _ = DS.removeFirst(ds);
        expect.list(toList()).toEqual([]);
      });

      test("removeFirstExn", ({expect}) => {
        let {toList, reset} = setup();

        let ds = reset([1, 2, 3]);
        DS.removeFirstExn(ds);
        expect.list(toList()).toEqual([2, 3]);

        let ds = reset([1, 2, 3]);
        expect.fn(() => DS.removeFirstExn(ds)).toThrow();
        expect.list(toList()).toEqual([1, 2, 3]);
      });

      test("removeFirstN", ({expect}) => {
        let {toList, reset} = setup();

        let ds = reset([1, 2, 3]);
        let _ = DS.removeFirstN(1, ds);
        expect.list(toList()).toEqual([2, 3]);

        let ds = reset([1, 2, 3]);
        let _ = DS.removeFirstN(2, ds);
        expect.list(toList()).toEqual([3]);

        let ds = reset([]);
        let _ = DS.removeFirstN(0, ds);
        expect.list(toList()).toEqual([]);

        let ds = reset([1, 2, 3]);
        let _ = DS.removeFirstN(1000, ds);
        expect.list(toList()).toEqual([1, 2, 3]);

        let ds = reset([]);
        let _ = DS.removeFirstN(1, ds);
        expect.list(toList()).toEqual([]);
      });

      test("removeFirstNExn", ({expect}) => {
        let {toList, reset} = setup();

        let ds = reset([1, 2, 3]);
        DS.removeFirstNExn(1, ds);
        expect.list(toList()).toEqual([2, 3]);

        let ds = reset([1, 2, 3]);
        DS.removeFirstNExn(2, ds);
        expect.list(toList()).toEqual([3]);

        let ds = reset([]);
        DS.removeFirstNExn(0, ds);
        expect.list(toList()).toEqual([]);

        let ds = reset([1, 2, 3]);
        expect.fn(() => DS.removeFirstNExn(1000, ds)).toThrow();
        expect.list(toList()).toEqual([1, 2, 3]);

        let ds = reset([]);
        expect.fn(() => DS.removeFirstNExn(1, ds)).toThrow();
        expect.list(toList()).toEqual([]);
      });

      test("updateFirst", ({expect}) => {
        let {toList, reset} = setup();

        let ds = reset([1, 2, 3]);
        let _ = DS.updateFirst(x => x + 1, ds);
        expect.list(toList()).toEqual([2, 2, 3]);

        let ds = reset([]);
        let _ = DS.updateFirst(x => x + 1, ds);
        expect.list(toList()).toEqual([]);
      });

      test("updateFirstExn", ({expect}) => {
        let {toList, reset} = setup();

        let ds = reset([1, 2, 3]);
        DS.updateFirstExn(x => x + 1, ds);
        expect.list(toList()).toEqual([2, 2, 3]);

        let ds = reset([]);
        expect.fn(() => DS.updateFirstExn(x => x + 1, ds)).toThrow();
        expect.list(toList()).toEqual([]);
      });
    });
  };
};
