
declare
	var x ;
	proc q() is
		declare
			var w
		begin
			x := x + 1 ;
			w := 50
		end
begin
	x := 1 ;

	while ^(x > 4) do
		call q () 
	od

end
