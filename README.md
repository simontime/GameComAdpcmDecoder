# GameComAdpcmDecoder
Decodes Tiger Game.Com ADPCM.

You can find a compiled Windows .exe in [releases](https://github.com/simontime/GameComAdpcmDecoder/releases).

Usage via command line: `Decoder.exe <input audio clip/tgc rom> <output raw file>`

To play back the decoded sounds, use Audacity's raw data import feature⁠—unsigned 8-bit PCM, 1 channel, 8000Hz.
- Note: If converting an entire ROM, there will be some junk audio where other game data gets decoded into sound! This is normal, just skip past that until you find usable audio data.
