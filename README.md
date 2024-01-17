# fcitx5-ipa-sil

This is an IME for [fcitx5](https://fcitx-im.org/wiki/Fcitx_5) that brings support for the [SIL IPA](https://keyman.com/keyboards/sil_ipa) input method. Consider this layout to be in beta - the original SIL layout is in the table, and I am currently testing the functionality and considering if I should expand it to cover characters not covered by the original layout. Please open issues or pull requests for: broken character combinations, input bugs, or a better way to handle spaces following designated IME characters.

This allows the user to type IPA characters fairly easily by inputting only ASCII.

Here are a few examples of input to IPA conversion:

| IPA | input |
|-----|-------|
| ə   | `e=`  |
| ʃ   | `s=`  |
| ŋ   | `n>`  |
| a   | `a`   |

I originally forked [yukijou](https://git.kemonomimi.gay/yukijoou)'s original layout to add support for more characters and diacritic combinations, however I have now switched to a table-based method using [fcitx5-chinese-addons](https://github.com/fcitx/fcitx5-chinese-addons) and [libime](https://github.com/fcitx/libime).

I may eventually make modifications to the SIL layout as I think more about the practicality of certain input combinations.

## Building & trying it out!

Build or install with your package manager the [fcitx5-chinese-addons](https://github.com/fcitx/fcitx5-chinese-addons) and [libime](https://github.com/fcitx/libime) packages and their further dependencies. (I did consider stripping out the table library in the former so this could be installed as a single package, but it is not very big.)

```console
$ mkdir -p build/
$ cd build/
$ cmake ../ -DCMAKE_INSTALL_PREFIX=/usr
$ make
$ sudo make install
```

You can then restart fcitx5, and add the `SIL IPA` input method to your selected input methods.


# Credits

Original inspiration by [yukijou](https://git.kemonomimi.gay/yukijoou), whose code I used to figure out how these input methods work (or at least a small part of that). Most of the credit for the current code goes to the original developers of and current maintainers of fcitx5, fcitx5-chinese-addons, and libime.

