# Interesting fact

These files are from [python library Scipy](https://github.com/scipy/scipy/tree/main/scipy/special/cephes). Which in turn are modified files of the [Cephes](https://www.netlib.org/cephes/) library . I do not own any rights to them.

(However, I commented out warning messages :grin:)

The reason I copied them is to calculate the Incomplete elliptic integral of the second kind.
The cpp standard library [function](https://en.cppreference.com/w/cpp/numeric/special_functions/ellint_2) **std::ellint_2** has the following formula:
$$
E(k,\phi)  =  \int_0^{\phi}  \sqrt{1  -  k^2  sin^2\theta}d\theta
$$

but I need:

$$
E(m,\phi)  =  \int_0^{\phi}  \sqrt{1  -  m  sin^2\theta}d\theta
$$

which is provided by Scipy's **ellipeinc** [function](https://docs.scipy.org/doc/scipy/reference/generated/scipy.special.ellipeinc.html#scipy.special.ellipeinc).