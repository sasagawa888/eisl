;; Edlis unicode test
;; error -tai -arabian -vietnam -hindy -tamil -nepal
;; 不具合　タイ語　アラビア語　ベトナム語　ヒンディー語　タミル語　ネパール語

(defglobal c #\本)
#|
日本語
マルチ行コメント
|#

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
          ((string= x "ขอขอบคุณ")'tai)
          ((string= x "شكرًا لك") 'arabian)
          ((string= x "Баярлалаа") 'mongolia)
          ((string= x "Благодаря ти") 'bulgaria)))

