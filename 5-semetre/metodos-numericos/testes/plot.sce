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

function y = f(x)
    y = x^3 - 2*x - 5;
endfunction

root = bisection(f, 2, 3, 1e-6, 100);
disp("Root: " + string(root));

