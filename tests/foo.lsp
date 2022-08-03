;; Edlis unicode test
;; error -tai -arabian -vietnam -hindy -tamil -nepal

(defun bar (x) 
    (cond ((string= x "thank you") 'english)
          ((string= x "ありがとう") 'japan)
          ((string= x "Дякую") 'ukraine)
          ((string= x "Спасибо") 'russia)
          ((string= x "Teşekkürler") 'turkey)
          ((string= x "رەھمەت سىزگە") 'wiggle)
          ((string= x "谢谢") 'china)
          ((string= x "감사합니다") 'korea)
          ((string= x "Благодаря ти") 'bulgaria)
          ((string= x "תודה") 'hebrew)
          ((string= x "Ευχαριστώ") 'greece)
          ((string= x "Děkuji") 'czechoslovak)
          ((string= x "Ačiū") 'lithuania)
          ((string= x "ขอขอบคุณ") 1)
          ((string= x "Баярлалаа") 'mongolia)
          ((string= x "Благодаря ти") 'bulgaria)))

          
          
          
          
     










