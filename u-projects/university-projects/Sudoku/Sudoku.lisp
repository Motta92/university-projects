; ---------------------------------------------------

; Taller calificable
; Sudoku
; Realizado por Carlos Motta

; Primera matriz de prueba
(setq sud1 '((* * * 4 7 8 * 3 *)
             (* * * * * * 9 * *)
             (* * 2 * 1 * * * *)
             (6 * * 9 * * * * *)
             (9 4 * * * * 5 * *)
             (* * * 5 * * 3 * 7)
             (* * 5 * 8 * 1 * *)
             (* 9 * * * 3 * * 6)
             (1 * * * * * * 2 *)))

; Segunda matriz de prueba
(setq sud2 '((5 3 * * 7 * * * *)
             (6 * * 1 9 5 * * *)
             (* 9 8 * * * * 6 *)
             (8 * * * 6 * * * 3)
             (4 * * 8 * 3 * * 1)
             (7 * * * 2 * * * 6)
             (* 6 * * * * 2 8 *)
             (* * * 4 1 9 * * 5)
             (* * * * 8 * * 7 9)))

; Dominio de posibles valores que se pueden poner en el sudoku
(setq d '(1 2 3 4 5 6 7 8 9))

; Funcion que me permite obtener una fila de la matriz dada la fila
(defun obtenerFila (sudoku f ft)
  (cond
    ((not(equal f ft)) (obtenerFila (cdr sudoku) f (+ ft 1)))
    (t (car sudoku))
  )
)

; Funcion que me permite obtener un elemento dada la columna dentro de una fila
(defun obtenerCol (sudoku c ct)
  (cond
    ((not(equal c ct)) (obtenerCol (cdr sudoku) c (+ ct 1)))
    (t (car sudoku))
  )
)

; Funcion que me permite obtener una columna de la matriz la columna
(defun obtenerColumnaCompleta (sudoku c ct)
  (cond
    ((null sudoku) nil)
    (t (append (list (obtenerCol (car sudoku) c ct)) (obtenerColumnaCompleta (cdr sudoku) c ct)))
  )
)

; Funcion quem e permite obtener el comienzo de uno de los cuadros de la matriz dada la columna
(defun obtenerInicio_C(sudoku c)
  (* (floor c 3) 3)
)

; Funcion quem e permite obtener el comienzo de uno de los cuadros de la matriz dada la columna
(defun obtenerInicio_F(sudoku f)
  (* (floor f 3) 3)
)

; Funcion que me permite quitar las filas innecesarias para empezar a buscar las columnas de un cuadro
(defun ajustarFilaSudokuCuadro(sudoku f ft)
  (cond
    ((not(equal f ft)) (ajustarFilaSudokuCuadro (cdr sudoku) f (+ ft 1)))
    (t sudoku)
  )
)

; Funcion que me permite obtener un cuadro
(defun evaluarCuadro(sudoku f c ft ct)
  (cond
    ((equal f ft) nil)
    ((not(equal c ct)) (append (list (nth ct (car sudoku))) (evaluarCuadro sudoku f c ft (+ ct 1))))
    (t (evaluarCuadro (cdr sudoku) f c (+ ft 1) (- c 3)))
  )
)

; Funcion que obtiene el cuadro hecha de manera que se pudiera visualizar mejor el procedimiento
(defun obtenerCuadrado(sudoku f c)
  (setq inicioF (obtenerInicio_F sudoku f))
  (setq inicioC (obtenerInicio_C sudoku c))
  (evaluarCuadro (ajustarFilaSudokuCuadro sudoku inicioF 0) (+ inicioF 3) (+ inicioC 3) inicioF inicioC)
)

; Funcion que me obtiene el valor de una casilla de la matriz dado una fila f y una columna c
(defun obtenerValor(sudoku f c ft ct)
  (obtenerCol (obtenerFila sudoku f ft) c ct)
)

; Funcion que construye una fila dada la columna
(defun armarFila(sudoku c ct n)
  (cond
    ((null sudoku) nil)
    ((not (equal c ct)) (append (list (car sudoku)) (armarFila (cdr sudoku) c (+ ct 1) n)))
    (t (append (list n) (armarFila (cdr sudoku) c (+ ct 1) n)))
  )
)

; Funcion que me permite insertar un valor dentro de la matriz
(defun insertarValor (sudoku f c ft ct n)
  (cond
    ((null sudoku) nil)
    ((not (equal f ft)) (append (list (car sudoku)) (insertarValor (cdr sudoku) f c (+ ft 1) ct n)))
    (t (append (list (armarFila (car sudoku) c ct n)) (insertarValor (cdr sudoku) f c (+ ft 1) ct n)))
  )
)

; devuelve t si no se encontraron mas de 1 ocurrencia de un valor 
; de d en una fila del sudoku, por ejemplo:
; (1 1 * * * * * * *) = nil
; (1 * * * * * * * *) = t
; d hace referecia al dominio = (1 2 3 4 5 6 7 8 9)
(defun revisarD (d sudoku flag)
  (cond
    ((null sudoku) (if (<= flag 1) t nil))
    ((equal d (car sudoku)) (revisarD d (cdr sudoku) (+ flag 1)) )
    (t (revisarD d (cdr sudoku) flag))
  )
)

; Las siguientes funciones tinen funcionalidades iguales, se separan para mejor entendimiento

; devuelve t si no en toda la horizontal no se presentan problemas
; y nil si la fila no es correcta
; Esta funcion recibe una fila de la matriz como entrada
(defun validarH (sudoku d)
  (cond
    ((null d) t)
    ((equal (revisarD (car d) sudoku 0) t) (validarH sudoku (cdr d)))
    (t nil)
  )
)

; devuelve t si no en toda la horizontal no se presentan problemas
; y nil si la fila no es correcta
; Esta funcion recibe una fila de la matriz como entrada
(defun validarV (sudoku d)
  (cond
    ((null d) t)
    ((equal (revisarD (car d) sudoku 0) t) (validarV sudoku (cdr d)))
    (t nil)
  )
)

; devuelve t si no en toda la horizontal no se presentan problemas
; y nil si la fila no es correcta
; Esta funcion recibe una fila de la matriz como entrada
(defun validarC (sudoku d)
  (cond
    ((null d) t)
    ((equal (revisarD (car d) sudoku 0) t) (validarC sudoku (cdr d)))
    (t nil)
  )
)

; Funcion que me valida las restricciones del juego
; Retorna True si efectivamente las cumple
; Retorna False si no las cumple
(defun esValido (sudoku k f c ft ct)
;          Validar horizontal     
  (if (and (validarH (obtenerFila sudoku f ft) d) 
;          Validar vertical
           (validarV (obtenerColumnaCompleta sudoku c ct) d) 
;          validar Cuadrado
           (validarC (obtenerCuadrado sudoku f c) d)) t nil)
)


; Funcion que me quita los asteriscos de una lista
(defun quitarAsteriscos (lista)
  (cond
    ((null lista) nil)
    ((equal (car lista) '*) (quitarAsteriscos (cdr lista)))
    (t (append (list (car lista)) (quitarAsteriscos (cdr lista))))
  )
)

; Funcion que me permite saber que valores posibles puede tomar una casilla dentro de la matriz
(defun obtenerConjuntoValores (sudoku f c ft ct d)
  (setq result1 (obtenerFila sudoku f ft))
  (setq result2 (obtenerColumnaCompleta sudoku c ct))
  (setq result3 (obtenerCuadrado sudoku f c))

  (set-difference d (quitarAsteriscos (union (union result1 result2) result3)))
)

; Funcion que me permite construir la matriz de arco-consistencia
(defun arcoconsistencia (sudoku k d)
  (setq fila (floor k 9))
  (setq col (mod k 9))
  (cond
    ((equal k 81) nil)
    ((not (equal (obtenerValor sudoku fila col 0 0) '*)) (append (list (list (obtenerValor sudoku fila col 0 0))) (arcoconsistencia sudoku (+ k 1) d)))
    (t (append (list (obtenerConjuntoValores sudoku fila col 0 0 d)) (arcoconsistencia sudoku (+ k 1) d) ))
  )
)

; Solucion de backtracking recursiva

(defun bt (sudoku arcos dominio k)
  (setq fila (floor k 9))
  (setq col (mod k 9))
  (cond
    ((null arcos) sudoku)
    ((equal (obtenerValor sudoku fila col 0 0) '*) (aux sudoku (car arcos) arcos dominio k))
    (t (bt sudoku (cdr arcos) dominio (+ k 1)))
  )
)

(defun aux (sudoku arco arcos dominio k)
  (setq fila (floor k 9))
  (setq col (mod k 9))
  (cond
    ((null arco) nil)
    ((esValido (insertarValor sudoku fila col 0 0 (car arco)) k fila col 0 0) 
      (or (bt (insertarValor sudoku fila col 0 0 (car arco)) (cdr arcos) dominio (+ k 1)) 
          (aux sudoku (cdr arco) arcos dominio k)
      ) 
    )
    (t (aux sudoku (cdr arco) arcos dominio k))
  )
)

; Primer llamado del backtracking
(defun SolucionarSudoku (sudoku d)
  (bt sudoku (arcoconsistencia sudoku 0 d) d 0)
)
