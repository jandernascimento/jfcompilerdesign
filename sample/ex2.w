
declare
	var x ;
	proc p(a, b) is 
		declare 
			var w  
		begin 
			x := 20  
		end ;
	proc q() is
		declare
			var w
		begin
			x := 0 
		end;
	proc r(z) is
		declare 
			var t
		begin
			t:=z+2*x ;
			call q()
		end 
	  

begin

	x := 1 	;
	call p (12, x+1) 
end
