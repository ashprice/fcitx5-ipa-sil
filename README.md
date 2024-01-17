# fcitx5-ipa-sil

This is an IME for [fcitx5](https://fcitx-im.org/wiki/Fcitx_5) that brings support for the [SIL IPA](https://keyman.com/keyboards/sil_ipa) input method.

This allows the user to type IPA characters fairly easily by inputting only ASCII.

Here are a few examples of input to IPA conversion:

| IPA | input |
|-----|-------|
| ə   | `e=`  |
| ʃ   | `s=`  |
| ŋ   | `n>`  |
| a   | `a`   |

**This is still a work in progress**: I forked [yukijou](https://git.kemonomimi.gay/yukijoou)'s original layout to add support for more characters and diacritic combinations. I haven't looked into how to support stacked diacritics yet, so if you want to give a pull request or start your own fork, please let me know! (I will probably package this for the Arch user repository soon.)

I may eventually make modifications to the SIL layout as I think more about the practicality of certain input combinations.

## Building & trying it out!

```console
$ mkdir -p build/
$ cd build/
$ cmake ../ -DCMAKE_INSTALL_PREFIX=/usr
$ make
$ sudo make install
```

You can then restart fcitx5, and add the `SIL IPA` input method to your selected input methods.


# Credits

Original development by [yukijou](https://git.kemonomimi.gay/yukijoou). I have created a fork of their original layout so that I can customize it and add further character support - I wasn't aware of how to write fcitx5 layouts before looking at theirs, and will probably write some more in addition to this one, but all original credit for the basic code goes to them.

