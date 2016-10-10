; ---------------------------------------------------

; Proyecto del Curso
; Realizado por Carlos Fernando Motta

; FORWARD!

(setq alphabet '(a b c d e f g h i j k l m n o p q r s t u v w x y z))

(setq kb '(  (((PAmerican x)(PWeapon y)(PSells x y z)(PHostile z)) (PCriminal x))
             (()(POwns Nono M1))
             (()(PMissile M1))
             (((PMissile x)(POwns Nono x)) (PSells West x Nono))
             (((PMissile x)) (PWeapon x))
             (((PEnemy x America)) (PHostile x))
             (()(PAmerican West))
             (()(PEnemy Nono America)) ))

(setq query '(PCriminal West))


(setq kb2 '(( ((PGreedy x)(PKing x)) (PEvil x))
             (()(PKing Mario))
             (()(PGreedy Motz))
             (()(PEnemy Nono America)) 
             ))

(setq query2 '(PEvil Motz))

(setq kb3 '((((PKing x)(PGreedy x)) (PEvil x))
 (()(PKing John)) 
 (()(PGreedy Jenny)) 
 (()(PKing Jenny))
 (()(PGreedy John)) 
 (()(PGreedy Joan)) 
 (()(PKing Juan)) )) 

(setq query3 '(PEvil John)) 
(setq query4 '(PEvil Jenny)) 
(setq query5 '(PEvil Joan)) 
(setq query6 '(PEvil Juan))

(setq qp1 '(PPariente Carlos)) 

(setq kbp '( (((PHombre x)(PMadre z x)(PMadre z y)(PNIgual x y))(PHermano x y))
             (((PHombre x)(PPadre y x))(PHijo x y)) 
             (((PMujer x)(PPadre y x))(PHija x y)) 
             (()(PMadre Luisa Carlos))
             (()(PMadre Luisa Camilo))
             (((PHombre x)(PMadre y x)(PTia y z))(PPrimo x z))
             (((PMujer x)(PMadre y x)(PTia y z))(PPrima x z))
             (((PMujer x)(PMadre y z)(PHermana x y))(PTia y z))
             (((PHombre x)(PHijo x y)(PHijo y z)(PHermano z w)(PPadre w v)(PPadre v c))(PPrimoDos x c))
             (((PHombre x)(PHijo x y)(PHermano y z))(PSobrino x z))
             (((PMujer x)(PHija x y)(PHermano y z))(PSobrina x z))
             (((PHombre x)(PPadre x y)(PConyuge y z))(PSuegro x z))
             (((PMujer x)(PMadre x y)(PConyuge y z))(PSuegra x z))
             (((PHombre x)(PConyuge x y)(PHija y z))(PYerno x z))
             (((PMujer x)(PConyuge x y)(PHijo y z))(PNuera x z))
             (((PHombre x)(PHermano x y)(PConyuge y z))(PCunado x z))
             (((PMujer x)(PHermana x y)(PConyuge y z))(PCunada x z))
             (((PHombre x)(PHermano x y)(PPadre y z))(PPariente x z))
             (()(PHombre Carlos))
             (()(PHombre Camilo)) 
             (()(PMujer Luisa))
             (()(PMujer Stephany)) 
             (()(PHombre Teo))
             (()((PPadre Teo Carlos)))
             (()(PHermano Hugo Maria))
             (()(PMadre Luisa Juan))
             (()(PPadre Hugo Juan))
             (()(PTia Maria Juan))
             (()(PPadre Juan Clara))
             (()(PMadre Elsa Clara))
             (()(PMadre Clara Bruno))
             (()(PMadre Maria Jesus))
             (()(PPadre Jose Jesus))
             (()(PTio Hugo de Jesus))
             (()(PPadre Jesus Jorge))
             (()(PMadre Ana Jorge))
             (()(PPadre Jorge Bruno))
             (()(PNuera Elsa Luisa))
             (()(PNuera Elsa Hugo))
             (()(PNuera Ana Maria))
             (()(PNuera Ana Jose))
             (()(PPrimo Juan Jesus))
             (()(PAbuelo Hugo Clara))
             (()(PAbuela Luisa Clara))
             (()(PAbuelo Jose Jorge))
             (()(PAbuela Maria Jorge))
             (()(PAbuelo Juan Bruno))
             (()(PAbuelo Jesus Bruno))
             (()(PAbuela Elsa Bruno))
             (()(PAbuela Ana Bruno))
             (()(PMujer Luisa))
             (()(PMujer Maria))
             (()(PMujer Elsa))
             (()(PMujer Ana))
             (()(PMujer Clara))
             (()(PHombre Hugo))
             (()(PHombre Jose))
             (()(PHombre Juan))
             (()(PHombre Jesus))
             (()(PHombre Jorge))
             (()(PHombre Bruno)) 

                 ))

(setq hermanos '(PHermano John John)) 
(setq hermanos2 '(PHermano Juan Juan)) 
(setq hermanos3 '(PHermano John Juan)) 
(setq hermanos4 '(PHermano Juan John))

; Funcion que dada la base de conocimiento y un query utiliza forward para indetificar 
; si se pudo inferir dicho query

(defun resolverForward (kb query)
  (forward kb nil query)
)

; TAREAS QUE FALTAN MEJORAR!!!
; Arreglar las sustituciones que devuleve hacerUnificaciones
; Mejorar funcionalidad de validarUnificaciones

; Funcion que dado la base de conocimiento, una segunda base para comparar y el query
; devuelve true si se pudo inferir o false de lo contrario

(defun forward(kb kb2 query)
  (cond
    ((equal kb kb2) nil)
    ((not (equal (ResolverQuery (pruebaFinal kb query)) 'fail)) t)
    (t (forward (append (unPaso kb kb nil query) kb) kb query))
  )
)

; evalua si al final del proceso se logro inferir el query
(defun pruebaFinal(kb query)
  ;(mapcar 'unify (make-list (list-length kb) query) (obtenerHechos kb) kb)
  (validarPruebaFinal(mapcar 'unify (makeLista query (list-length kb)) (obtenerHechos kb) (makeLista nil (list-length kb)) ))
)

(defun validarPruebaFinal(q)
  (cond
    ((null q) 'fail)
    (t q)
  )
)

; Una vez realizado todo el forward, esta funcion permite identificar si fue posible resolverlo o no
(defun resolverQuery(map)
  (cond
    ((equal map 'fail) 'fail)
    ((null map) 'fail)
    ((equal (car map) nil) t)
    (t (resolverQuery (cdr map)))
  )
)

; Dadas las unificaciones, evalua que no sean fail
(defun validarUnificaciones(unificaciones)
  (cond
    ((equal unificaciones 'fail) 'fail)
    ((null unificaciones) t)
    ((not(equal (car unificaciones) 'fail)) (validarUnificaciones (cdr unificaciones)))
    (t 'fail)
  )
)

; Funcion que hace lo mismo que make-list, la cual no me funciono
(defun makeLista(valor n)
  (cond
    ((> n 0) (cons valor (makeLista valor (- n 1))))
    (t nil)
  )
)

; Funcion que me permite obtener los hechos de la base de conocimiento
(defun obtenerHechos(kb)
  (cond
    ((null kb) nil)
    ((equal (caar kb) nil) (append (cdr (car kb)) (obtenerHechos (cdr kb))) )
    (t (obtenerHechos (cdr kb)))
  )
)

; Funcion que me permite dar un paso en el proceso de forward para asi ir evaluando cada sentencia
; de la base de conocimiento y ver si se puede inferir o no

(defun unPaso(kb kb2 new query)
  (cond
    ((null kb) new)
    ( (and (validarPruebaActual (puedoProbar (obtenerAntecedentes (car kb)) (obtenerHechos kb2) (obtenerHechos kb2) nil))
      (not (equal (obtenerAntecedentes (car kb)) nil)) 
        (notInNew (pruebe (puedoProbar (obtenerAntecedentes (car kb)) (obtenerHechos kb2) (obtenerHechos kb2) nil) (obtenerConsecuente (car kb)) ) new)
          (notInKb (pruebe (puedoProbar (obtenerAntecedentes (car kb)) (obtenerHechos kb2) (obtenerHechos kb2) nil) (obtenerConsecuente (car kb)) ) (obtenerHechos kb2)) 
      )
          (unPaso (cdr kb) kb2 (append (list (list () (pruebe (puedoProbar (obtenerAntecedentes (car kb)) (obtenerHechos kb2) (obtenerHechos kb2) nil) (obtenerConsecuente (car kb)) ) )) new) query))
    (t (unPaso (cdr kb) kb2 new query))
  )
)

(defun notInNew(elem new)
  (cond
    ((null new) t)
    ((equal elem (car new)) nil)
    (t (notInNew elem (cdr new)))
  )
)

(defun notInKb(elem kb)
  (cond
    ((null kb) t)
    ((equal elem (car kb)) nil)
    (t (notInNew elem (cdr kb)))
  )
)


(defun validarPruebaActual (unif)
  (cond
    ((equal unif nil) nil)
    (t t)
  )
)

(defun puedoProbar(ant hechos Allhechos unificaciones)
  (cond
    ;((equal (validarUnificaciones (mapcar 'unify  kb (obtenerHechos kb2) (makeLista nil (list-length kb)))) t) t)
    ((null ant) unificaciones)
    ((null hechos) unificaciones)
    ((and (evaluarHacerPrueba (hacerPrueba (car ant) (car hechos) unificaciones)) (notInUnif (hacerPrueba (car ant) (car hechos) unificaciones) unificaciones)) 
      (puedoProbar (cdr ant) Allhechos Allhechos (adicionarElemASust (hacerPrueba (car ant) (car hechos) unificaciones) unificaciones) ) )
    (t (puedoProbar ant (cdr hechos) Allhechos unificaciones))
  )
)

; Funcion auxiliar de puedoProbar
; Intenta probar cada antecedente
(defun hacerPrueba(ant hecho unif)
  (cond
    ((null hecho) nil)
    ((not (equal (obtenerUnificacion ant hecho) nil)) (obtenerUnificacion ant hecho))
    (t nil)
  )
)

(defun evaluarHacerPrueba (unif)
  (cond
    ((null unif) nil)
    ((not (equal (car unif) nil)) t)
    (t nil)
  )
)

(defun notInUnif (sust unif)
  (cond
    ((null unif) t)
    ((sustRepetido sust unif) t)
    (t nil)
  )
)

(defun adicionarElemASust(elem sust)
  (cond
    ((null sust) (append sust elem))
    ((not (elemRepetido elem sust)) (append sust elem))
    (t sust)
  )
)

(defun elemRepetido(elem sust)
  (cond
    ((null sust) nil)
    ((and (equal (caar elem) (caar sust) ) (equal (car (cdr (car elem))) (car (cdr (car sust))) ) ) t)
    (t (elemRepetido elem (cdr sust)))
  )
)

(defun sustRepetido(elem sust)
  (cond
    ((null sust) nil)
    ((and (equal (caar elem) (caar sust) ) (equal (car (cdr (car elem))) (car (cdr (car sust))) ) ) t)
    (t (elemRepetido elem (cdr sust)))
  )
)

(defun obtenerUnificacion(ant hechos)
  (cond
    ((null hechos) nil)
    ((not (equal (validarUnificaciones (unify ant hechos nil)) 'fail)) (append (unify ant hechos nil) (obtenerUnificacion ant (Cdr hechos))))
    (t (obtenerUnificacion ant (cdr hechos)))
  )
)

; Dada la regla y la base de conocimiento probar y devolver el hecho generado
(defun pruebe(subs kb)
  ;(append (list ()) kb)
  (cond
    ((null kb) nil)
    (t (obtenerNewInferencia subs kb))
  )
)

(defun obtenerNewInferencia(subs con)
  (cond
    ((null subs) nil)
    ;(t (append (substituir subs con) (obtenerNewInferencia (cdr subs) con) ))
    (t (append (substituir subs con) (obtenerNewInferencia (cdr subs) con) ))
  )
  
)
(defun substituir(subs con)
  (cond
    ((null subs) nil)
    (t (append (construirSustitucion (car subs) con) (substituir (cdr subs) con)) )
  )
)

; Se asume que se pasan listas limpias-unicas
(defun construirSustitucion(sub con)
  (cond
    ((null con) nil)
    ((equal (car sub) (car con)) (cons (car (cdr sub)) (construirSustitucion sub (cdr con))) )
    (t (cons (car con) (construirSustitucion sub (cdr con)) ) )
  )
)

;(defun substituir(subs con)
;  (cond
;    ((null subs) con)
;    ((equal (caar subs) (car (cdr con))) (cons (car con) (cdr (car subs)) ))
;    (t (substituir (cdr subs) con))
;  )
;)


; Funcion tonta que me permite entender un poco mejor el codigo al leerlo
(defun obtenerAntecedentes(x)
  (car x)
)

; Funcion tonta que me permite entender un poco mejor el codigo al leerlo
(defun obtenerConsecuente(x)
  (car (cdr x))
)

; Funcion que permite unificar x y
(defun unify(x y subs)
  (cond
    ((equal subs 'fail) 'fail)
    ((equal x y) subs)
    ((esVar x) (unify_var x y subs))
    ((esVar y) (unify_var y x subs))
    ((and (esPred  x) (esPred y) (igualar x y)) (unify (cdr x)(cdr y) subs))
    ((and (esLista x) (esLista y)) (unify (cdr x)(cdr y)(unify (car x)(car y) subs)))
    (t 'fail)
  )
)

; Funcion auxiliar de unify
(defun unify_var(var x subs)
  (cond
    ((Pertenece var subs) (unify (getValue var subs) x subs))
    ((Pertenece x subs) (unify (getValue x subs) var subs))
    ((Aparece var x) 'fail)
    (t (append (list (list var x)) subs))
  )
)

;(symbol-name 'some-symbol) symbol to string
;(intern "some-string") string to symbol

; Funcion que me permite saber si x es miembro del alfabeto
; Pues se asume que las variables son letras del alfabeto
(defun isMember(x)
  (cond
    ((equal (member x alphabet) nil) nil)
    (t t)
  )
)

;(symbol-name 'some-symbol) symbol to string
;(intern "some-string") string to symbol

; Retorna true si x es una variable
(defun esVar(x)
  (cond
    ((esLista x) nil)
    ((and (not (equal (substring (symbol-name x) 0 1) "P")) 
          (isMember x))  t) 
    (t nil)
  )
)

; Me permite saber si x y y son son listas o no para poder aplicar las operaciones respectivas
(defun igualar(x y)
  (cond
    ((and (esLista x) (esLista y)) (equal (car x) (car y)))
    (t (equal x y))
  )
)

;(symbol-name 'some-symbol) symbol to string
;(intern "some-string") string to symbol

; Retorna true si x es un predicado
(defun esPred(x)
  (cond
    ((esLista x) nil)
    ((equal (substring  (symbol-name  x) 0 1) "P") t)
    (t nil)
  )
)

; Retorna true si x es una lista
(defun esLista(x)
  (cond
    ((listp x) t) ;retorna true para cada lista correcta
    (t nil)
  )
)

; Obtiene una lista dentro de subs que hace match con x 
; Se asume que subs es una lista con listas de parejas que identifican la substitucion
(defun pertenece(x subs)
  (cond
    ((null subs) nil)
    ((equal (car (car subs)) x) t)
    (t (pertenece x (cdr subs)))
  )
)

; Retorna t si x es igual a y
(defun aparece(x y)
  (cond
    ((equal x y) t)
    (t nil)
  )
)

; Obtiene la sustitucion del elemento x dentro de subs
(defun getValue(x subs)
  (cond
    ((null subs) nil)
    ((equal (car (car subs))  x) (car (cdr (car subs))) )
    (t (pertenece x (cdr subs)))
  )
)

; BACKWARD!!

; funcion que resuelve el query usando el algoritmo backward
(defun resolverBackward (kb query)
  (backward kb query nil) ; sust inicia como nil
)

; Funcion backward principal
(defun backward (kb query sust)
  (cond
    ((null kb) nil)
    ((AllFail (auxBackward1 kb query sust)) nil)
    (t (unPasoAtras kb kb query sust)) ; A diferencia de forward, se da un paso hacia atras
  )
)


(defun auxBackward1 (kb query sust)
  (mapcar 'unify (mapcar 'getConsecuent  kb) (makeLista (validateSust (applySust sust query sust) query) (list-length kb)) (makeLista nil (list-length kb)))
  ;(mapcar 'unify (mapcar 'getConsecuent  kb) (makeLista (applySust query sust) (list-length kb)) (makeLista nil (list-length kb)))
)

(defun unPasoAtras (kb kb2 query sust)
  (cond
    ((null kb) nil)
    ((not (equal (unify (getConsecuent (car kb)) query nil) 'fail))
      (let ( (newsust  (unify (getConsecuent (car kb)) query nil)) ) 
        (cond 
          ((propagate kb2 (getAnt (car kb)) newsust) t)
          (t (unPasoAtras (cdr kb) kb2 query newsust))
        )
      )
    )
    (t (unPasoAtras (cdr kb) kb2 query sust))
  )
)

(defun propagate (kb listAnt sust)
  (cond
    ((null listAnt) t)
    ((backward kb (car listAnt) sust) (propagate kb (cdr listAnt) sust))
    (t nil)
  )
)

(defun adicionarSust (kb query sust)
    (let ((unification (unify (getConsecuent (car kb)) query nil)) )
      (cond
        ((validateDuplicates sust unification) (append sust unification ))
        (t sust)
      )
    ) 
  )

(defun validateDuplicates (sust newItem)
  (cond
    ((null sust) t)
    ((equal (car sust) (car newItem)) nil)
    (t (validateDuplicates (cdr sust) newItem))
  )
)

(defun getConsecuent (kb)
  (car (cdr kb))
)

(defun getAnt (kb)
  (car kb)
)

;(defun applySust (query sust)
;  (cond
;    ((null sust) query)
;    ((equal (car (car sust)) (car(cdr query))) (cons (car query) (cdr (car sust))) )
;    (t (applySust query (cdr sust)))
;  )
;)

(defun applySust(subs con sust)
  (cond
    ((null subs) sust)
    (t (applySust (cdr subs) con (construirSustitucionB (car subs) con)) ) 
  )
)

(defun validateSust(sust con)
  (cond
    ((null sust) con)
    (t sust)
  )
)

; Se asume que se pasan listas limpias-unicas
(defun construirSustitucionB(sub con)
  (cond
    ((null con) nil)
    ((equal (car sub) (car con)) (cons (car (cdr sub)) (construirSustitucion sub (cdr con))) )
    (t (cons (car con) (construirSustitucion sub (cdr con)) ) )
  )
)


(defun allFail (test)
  (cond
    ((null test) t)
    ((not (equal (car test) 'fail)) nil)
    (t (allFail (cdr test)))
  )
)

(defun notAllFail (test)
  (cond
    ((null test) nil)
    ((not (equal (car test) 'fail)) t)
    (t (notallFail (cdr test)))
  )
)
