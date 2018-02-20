; ModuleID = 'main'

define internal void @main() {
main:
	  br label %scope
	    ret void

		scope:                                            ; preds = %main
		  ret void
}

