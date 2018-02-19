; ModuleID = 'main'

define internal void @main() {
entry:
  br i1 true, label %then, label %else
    ret void

	then:                                             ; preds = %entry
	  %x = alloca i64
	    store i64 15, i64* %x
		  br label %merge

		  else:                                             ; preds = %entry
		    %y = alloca i64
			  store i64 5, i64* %y
			    br label %merge

				merge:                                            ; preds = %else, %then
				  ret void
				  }

