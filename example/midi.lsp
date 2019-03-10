;;for Windows
;; tarai function music with Windows MIDI API

(c-include "<windows.h>")
(c-include "<mmsystem.h>")
(c-option "-lwinmm")
(c-define "MIDIMSG(status,channel,data1,data2)"
          "( (DWORD)((status<<4) | channel | (data1<<8) | (data2<<16)) )")
(c-lang "HMIDIOUT hMidiOut;")

(defun midi-out-open ()
  (c-lang "midiOutOpen(&hMidiOut, MIDI_MAPPER, 0, 0, CALLBACK_NULL);" )
  t)

(defun midi-out-close ()
  (c-lang "midiOutClose(hMidiOut);")
  t)

(defun midi-out-short-msg (st ch d1 d2)
  (if (not (integerp st)) (error "midi-out-short-msg" st))
  (if (not (integerp ch)) (error "midi-out-short-msg" ch))
  (if (not (integerp d1)) (error "midi-out-short-msg" d1))
  (if (not (integerp d2)) (error "midi-out-short-msg" d2))

  (c-lang "midiOutShortMsg(hMidiOut,MIDIMSG((BYTE)(INT_MASK & ST),(BYTE)(INT_MASK & CH),(BYTE)(INT_MASK & D1),(BYTE)(INT_MASK & D2)));")
  t)

(defun open-midi ()
  (midi-out-open))

(defun close-midi ()
  (midi-out-close))

(defglobal volume 127)

(defglobal tempo 240)

(defglobal channel 0)

(defun note-on (n)
  (midi-out-short-msg #x9 channel n volume))

(defun note-off (n)
  (midi-out-short-msg #x8 channel n volume))

(defun all-note-off ()
  (midi-out-short-msg #xb channel #x7b 0))

(defun all-sound-off ()
  (midi-out-short-msg #xb channel #x78 0))

(defun reset-all-controller ()
  (midi-out-short-msg #xb channel #x79 0))

(defun voice (n)
  (midi-out-short-msg #xc channel n 0))

(defun sleep (n)
  (for ((i (* n 1000000) (- i 1)))
       ((<= i 0) t)))


(defun tarai (x y z)
  (note-on (+ (* 2 x) 72))
  (sleep 100)
  (note-on (+ (* 2 y) 72))
  (sleep 100)
  (note-on (+ (* 2 z) 72))
  (sleep 100)
  (if (<= x y)
      y
      (tarai (tarai (- x 1) y z)
             (tarai (- y 1) z x)
             (tarai (- z 1) x y))))
