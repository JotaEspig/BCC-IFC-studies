library("ggplot2")

bissection = function(fn, a, b, k, k_max) {
    mid = (a + b) / 2
    if (fn(a) * fn(mid) < 0) {
        return(bissection(fn, a, mid, k+1, k_max))
    } else if (fn(mid) * fn(b) < 0) {
        return(bissection(fn, mid, b, k+1, k_max))
    }

    return(mid)
}

options(browser="brave")

eq = function(x) {
    return(x*x)
}

bisec = bissection(eq, -50, 50, 0, 100)

print(bisec)

curve(eq, -50, 50)

browseURL("Rplots.pdf")
