function root = bisection(f, a, b, tol, max_iter)
    // Ensure that f(a) and f(b) have opposite signs
    if f(a) * f(b) >= 0 then
        error("The function must have opposite signs at a and b.");
    end
    
    iter = 0;
    while (b - a) / 2 > tol & iter < max_iter do
        c = (a + b) / 2;
        
        if f(c) == 0 then
            root = c;
            return;
        elseif f(a) * f(c) < 0 then
            b = c;
        else
            a = c;
        end
        
        iter = iter + 1;
    end
    
    root = (a + b) / 2;
endfunction

function r = fixed_point(g, x0, tol, max_iter)
    x = x0;
    iter = 0;
    while iter < max_iter do
        x_new = g(x);
        
        if abs(x_new - x) < tol || abs(x_new) < tol then
            r = x_new;
            return;
        end
        
        x = x_new;
        iter = iter + 1;
    end
    
    r = x;
endfunction
