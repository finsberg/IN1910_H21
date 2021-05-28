
def mandelbrot_pixel(c, maxiter):
    z = 0

    for n in range(maxiter):
        z = z*z + c
        if abs(z) > 2:
            return n

    return 0

def compute(yj, x, maxiter):
    c = [xi + 1j*yj for xi in x]
    return list(map(mandelbrot_pixel, c, [maxiter]*len(c)))