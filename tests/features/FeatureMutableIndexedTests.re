open Rhythm;

module type DS = {
  type t('el);
  let toCamlList: t('el) => list('el);
  let fromCamlList: list('el) => t('el);
  include
    FeatureMutableIndexed.Interface with type tMutableIndexed('el) = t('el);
};

module type Output = {let register: Rely.Describe.describeFn(_) => unit;};

module Add = (DS: DS) : Output => {
  open Rely.Describe;

  type setup('el) = {
    ds: ref(DS.t('el)),
    getIndex: int => 'el,
    reset: unit => unit,
  };

  let setup = list => {
    let ds = ref(DS.fromCamlList(list));
    let getIndex = i =>
      ds.contents |> DS.toCamlList |> CamlList.getIndexExn(i);
    let reset = () => ds.contents = DS.fromCamlList(list);
    {ds, getIndex, reset};
  };

  let register = describe =>
    describe("FeatureMutableIndexed", ({test}) => {
      test("setIndex", ({expect}) => {
        let {ds, getIndex, reset} = setup([0, 1, 2]);
        let setIndex = (i, el) => DS.setIndex(i, el, ds.contents);

        /* Examples */
        reset();
        let _ = setIndex(0, 100);
        expect.int(getIndex(0)).toBe(100);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);

        reset();
        let _ = setIndex(2, 100);
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(100);

        reset();
        let _ = setIndex(3, 100);
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);

        reset();
        let _ = setIndex(-1, 100);
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);
      });

      test("setIndexExn", ({expect}) => {
        let {ds, getIndex, reset} = setup([0, 1, 2]);
        let setIndexExn = (i, el) => DS.setIndexExn(i, el, ds.contents);

        /* Examples */
        reset();
        setIndexExn(0, 100);
        expect.int(getIndex(0)).toBe(100);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);

        reset();
        setIndexExn(2, 100);
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(100);

        reset();
        expect.fn(() => setIndexExn(3, 100)).toThrow();
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);

        reset();
        expect.fn(() => setIndexExn(-1, 100)).toThrow();
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);
      });

      test("updateIndex", ({expect}) => {
        let {ds, getIndex, reset} = setup([0, 1, 2]);
        let updateIndex = (i, fn) => DS.updateIndex(i, fn, ds.contents);
        let add100 = x => x + 100;

        /* Examples */
        reset();
        let _ = updateIndex(0, add100);
        expect.int(getIndex(0)).toBe(100);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);

        reset();
        let _ = updateIndex(2, add100);
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(102);

        reset();
        let _ = updateIndex(3, add100);
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);

        reset();
        let _ = updateIndex(-1, add100);
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);
      });

      test("updateIndexExn", ({expect}) => {
        let {ds, getIndex, reset} = setup([0, 1, 2]);
        let updateIndexExn = (i, fn) =>
          DS.updateIndexExn(i, fn, ds.contents);
        let add100 = x => x + 100;

        /* Examples */
        reset();
        updateIndexExn(0, add100);
        expect.int(getIndex(0)).toBe(100);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);

        reset();
        updateIndexExn(2, add100);
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(102);

        reset();
        expect.fn(() => updateIndexExn(3, add100)).toThrow();
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);

        reset();
        expect.fn(() => updateIndexExn(-1, add100)).toThrow();
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);
      });

      test("swap", ({expect}) => {
        let {ds, getIndex, reset} = setup([0, 1, 2]);
        let swap = (i, j) => DS.swap(i, j, ds.contents);

        /* Examples */
        reset();
        let _ = swap(0, 2);
        expect.int(getIndex(0)).toBe(2);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(0);

        reset();
        let _ = swap(1, 2);
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(2);
        expect.int(getIndex(2)).toBe(1);

        reset();
        let _ = swap(2, 1);
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(2);
        expect.int(getIndex(2)).toBe(1);

        reset();
        let _ = swap(0, 100);
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);

        reset();
        let _ = swap(-1, 1);
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);
      });

      test("swapExn", ({expect}) => {
        let {ds, getIndex, reset} = setup([0, 1, 2]);
        let swapExn = (i, j) => DS.swapExn(i, j, ds.contents);

        /* Examples */
        reset();
        swapExn(0, 2);
        expect.int(getIndex(0)).toBe(2);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(0);

        reset();
        swapExn(1, 2);
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(2);
        expect.int(getIndex(2)).toBe(1);

        reset();
        swapExn(2, 1);
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(2);
        expect.int(getIndex(2)).toBe(1);

        reset();
        expect.fn(() => swapExn(0, 100)).toThrow();
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);

        reset();
        expect.fn(() => swapExn(-1, 1)).toThrow();
        expect.int(getIndex(0)).toBe(0);
        expect.int(getIndex(1)).toBe(1);
        expect.int(getIndex(2)).toBe(2);
      });
    });
};
