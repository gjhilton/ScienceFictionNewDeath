#Science Fiction: New Death

Interactive scenography for the FACT exhibition, _Science Fiction: New Death_
http://www.fact.co.uk/projects/science-fiction-new-death.aspx

_Science Fiction: New Death_ is curated by Omar Kholeif (writer & curator) and Mike Stubbs (FACT Director)

Exhibition design: Venya Krutikov, Mike Lill, The Kazimier
http://www.fact.co.uk/projects/science-fiction-new-death/the-kazimier.aspx

## To build: Arduino

Copy `NewDeathLib` to Arduino Library folder

To enable sensor calibration mode, uncomment line 8 of `NewDeathLib/MotionTrigger.h`
ie

	#define SENSOR_CALIBRATION_MODE

## To build: Mac

You need to add the following items to `MacClientGallery1Entry/bin/data`

- DIN.otf
- loop.mp3
- release.mp3
- start.mp3

## Known Issues

Gallery2 is way off production ready as yet - just a quick end of the day bodge
