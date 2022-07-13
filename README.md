# AccentColorizer

Colorize Windows with accent color of your choice - without modifying system files

AccentColorizer patches Windows theme data in-memory and recolorizes everything as soon as you change the accent color.

Supported Windows Vista and higher.

Additional functionality:
* [AccentColorizer-E11](https://github.com/krlvm/AccentColorizer-E11) to colorize Windows 11 File Explorer icon glyphs
* [ContextMenuNormalizer](https://github.com/krlvm/ContextMenuNormalizer) to make context menus look more consistent on Windows 10
* [DragDropNormalizer](https://github.com/krlvm/DragDropNormalizer) to fix drag&drop overlay look on Windows 11 22H2

### Progress Bar colorization

AccentColorizer supports colorization of Progress Bars, but it is not recommended to enable, because it will make it difficult to distinguish between their states (progress bars may turn red to indicate an error, the disk full indicator turns red to indicate that space is running out). However, this is rarely used, and if you want to enable this feature, create the `HKEY_CURRENT_USER\Software\AccentColorizer` key in the registry and the DWORD value `ColorizeProgressBar`, set it to `1` and restart AccentColorizer.

This can be done from command line:
```
reg add "HKEY_CURRENT_USER\SOFTWARE\AccentColorizer" /v ColorizeProgressBar /t REG_DWORD /d 1 /f
```

## Gallery

![Windows 11](https://github.com/krlvm/AccentColorizer/blob/master/.screenshots/win11.png?raw=true)\
![Windows 10](https://github.com/krlvm/AccentColorizer/blob/master/.screenshots/win10.png?raw=true)\
![Windows 8](https://github.com/krlvm/AccentColorizer/blob/master/.screenshots/win8.png?raw=true)\
![Windows 7](https://github.com/krlvm/AccentColorizer/blob/master/.screenshots/win7.png?raw=true)

## Special thanks

Thanks to *@mcdenis* for his idea and work on original [AccentApplicator](https://github.com/mcdenis/AccentApplicator)\
Thanks to *@rounk-ctrl* and his work on [AccentApplicator](https://github.com/rounk-ctrl/AccentApplicator) for bringing this project back to live
