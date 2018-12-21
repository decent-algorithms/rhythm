module type Config = {
  type t('el);
  let toList: t('el) => list('el);
  let fromList: list('el) => t('el);
};

module type Interface = {
  type tSequence('el);

  let init: (int, int => 'el) => tSequence('el);

  let toSimpleList: tSequence('el) => SimpleListCore.t('el);
  let fromSimpleList: SimpleListCore.t('el) => tSequence('el);

  let toMutableArray: tSequence('el) => MutableArrayCore.t('el);
  let fromMutableArray: MutableArrayCore.t('el) => tSequence('el);

  let every: ('el => bool, tSequence('el)) => bool;
  let everyi: ((int, 'el) => bool, tSequence('el)) => bool;
  let forEach: ('el => unit, tSequence('el)) => unit;
  let forEachi: ((int, 'el) => unit, tSequence('el)) => unit;
  let none: ('el => bool, tSequence('el)) => bool;
  let nonei: ((int, 'el) => bool, tSequence('el)) => bool;
  let some: ('el => bool, tSequence('el)) => bool;
  let somei: ((int, 'el) => bool, tSequence('el)) => bool;

  let filterDrop: ('el => bool, tSequence('el)) => tSequence('el);
  let filterDropi: ((int, 'el) => bool, tSequence('el)) => tSequence('el);
  let filterKeep: ('el => bool, tSequence('el)) => tSequence('el);
  let filterKeepi: ((int, 'el) => bool, tSequence('el)) => tSequence('el);
  let map: ('a => 'b, tSequence('a)) => tSequence('b);
  let mapi: ((int, 'a) => 'b, tSequence('a)) => tSequence('b);
  let reverse: tSequence('el) => tSequence('el);
  let reduce: (('acc, 'el) => 'acc, 'acc, tSequence('el)) => 'acc;
  let reducei: (('acc, int, 'el) => 'acc, 'acc, tSequence('el)) => 'acc;
  let reduceReverse: (('acc, 'el) => 'acc, 'acc, tSequence('el)) => 'acc;
  let reduceReversei:
    (('acc, int, 'el) => 'acc, 'acc, tSequence('el)) => 'acc;

  let flatten: tSequence(tSequence('el)) => tSequence('el);
  let concat: (tSequence('el), tSequence('el)) => tSequence('el);
  let concatList: array(tSequence('el)) => tSequence('el);
  let concatList: list(tSequence('el)) => tSequence('el);
};

module Add =
       (Config: Config)
       : (Interface with type tSequence('el) = Config.t('el)) => {
  type tSequence('el) = Config.t('el);

  let init = (count, f) =>
    Caml.Array.init(count, f) |> MutableArrayCore.toList |> Config.fromList;

  let toSimpleList = ds => ds |> Config.toList |> SimpleListCore.fromList;
  let fromSimpleList = ds => ds |> SimpleListCore.toList |> Config.fromList;

  let toMutableArray = ds => ds |> Config.toList |> MutableArrayCore.fromList;
  let fromMutableArray = ds =>
    ds |> MutableArrayCore.toList |> Config.fromList;

  let everyi = (fn, ds) => {
    let list = Config.toList(ds);
    let list = ref(list);
    let result = ref(true);
    let i = ref(0);
    while (result^ && !SimpleListCore.isEmpty(list^)) {
      switch (list^) {
      | [hd, ...rest] =>
        list := rest;
        if (!fn(i^, hd)) {
          result := false;
        };
        incr(i);
      | _ => raise(Exceptions.InternalError("FeatureSequence.everyi"))
      };
    };
    result^;
  };

  let every = (fn, ds) => everyi((i, el) => fn(el), ds);

  let somei = (fn, ds) => {
    let list = Config.toList(ds);
    let list = ref(list);
    let result = ref(false);
    let i = ref(0);
    while (! result^ && !SimpleListCore.isEmpty(list^)) {
      switch (list^) {
      | [hd, ...rest] =>
        list := rest;
        if (fn(i^, hd)) {
          result := true;
        };
        incr(i);
      | _ => raise(Exceptions.InternalError("FeatureSequence.somei"))
      };
    };
    result^;
  };

  let some = (fn, ds) => somei((i, el) => fn(el), ds);

  let nonei = (fn, ds) => everyi((i, el) => !fn(i, el), ds);

  let none = (fn, ds) => nonei((i, el) => fn(el), ds);

  let forEachi = (fn, ds) => {
    let list = Config.toList(ds);
    Caml.List.iteri(fn, list);
  };

  let forEach = (fn, ds) => forEachi((i, el) => fn(el), ds);

  let reverse = ds => ds |> Config.toList |> Caml.List.rev |> Config.fromList;

  let reducei = (fn, initialValue, ds) => {
    let list = Config.toList(ds);
    let list = ref(list);
    let result = ref(initialValue);
    let i = ref(0);
    while (!SimpleListCore.isEmpty(list^)) {
      switch (list^) {
      | [hd, ...rest] =>
        list := rest;
        result := fn(result^, i^, hd);
        incr(i);
      | _ => raise(Exceptions.InternalError("FeatureSequence.reducei"))
      };
    };
    result^;
  };

  let reduce = (fn, initialValue, ds) =>
    reducei((acc, i, el) => fn(acc, el), initialValue, ds);

  let reduceReversei = (fn, initialValue, ds) => {
    let list = Config.toList(ds);
    let list = Caml.List.rev(list);
    let list = ref(list);
    let result = ref(initialValue);
    let i = Caml.List.length(list^) - 1;
    let i = ref(i);
    while (!SimpleListCore.isEmpty(list^)) {
      switch (list^) {
      | [hd, ...rest] =>
        list := rest;
        result := fn(result^, i^, hd);
        decr(i);
      | _ =>
        raise(Exceptions.InternalError("FeatureSequence.reduceReversei"))
      };
    };
    result^;
  };

  let reduceReverse = (fn, initialValue, ds) =>
    reduceReversei((acc, i, el) => fn(acc, el), initialValue, ds);

  let mapi = (fn, ds) => {
    let list = Config.toList(ds);
    let list = Caml.List.mapi(fn, list);
    Config.fromList(list);
  };

  let map = (fn, ds) => mapi((i, el) => fn(el), ds);

  let filterKeepi = (fn, ds) => {
    let list = Config.toList(ds);
    let list = ref(list);
    let resultRev = ref([]);
    let i = ref(0);
    while (!SimpleListCore.isEmpty(list^)) {
      switch (list^) {
      | [hd, ...rest] =>
        list := rest;
        if (fn(i^, hd)) {
          resultRev := [hd, ...resultRev^];
        };
        incr(i);
      | _ => raise(Exceptions.InternalError("FeatureSequence.filterKeepi"))
      };
    };
    resultRev^ |> Caml.List.rev |> Config.fromList;
  };

  let filterKeep = (fn, ds) => filterKeepi((i, el) => fn(el), ds);

  let filterDropi = (fn, ds) => filterKeepi((i, el) => !fn(i, el), ds);

  let filterDrop = (fn, ds) => filterDropi((i, el) => fn(el), ds);

  let concatArray = dsArray => {
    let arr1D = dsArray;
    let arr2D = Caml.Array.map(toMutableArray, arr1D);
    let lengths = Caml.Array.map(Caml.Array.length, arr2D);
    let sum = Caml.Array.fold_left((sum, x) => sum + x, 0, lengths);
    let arr = ref(0);
    let i = ref(0);
    let fullArray =
      Caml.Array.init(
        sum,
        _ => {
          while (i^ >= lengths[arr^]) {
            incr(arr);
            i := 0;
          };
          let value = arr2D[arr^][i^];
          incr(i);
          value;
        },
      );
    fromMutableArray(fullArray);
  };

  let concatList = dsList => dsList |> Caml.Array.of_list |> concatArray;

  let flatten = ds2D => ds2D |> toSimpleList |> concatList;

  let concat = (ds1, ds2) => concatList([ds1, ds2]);
};
