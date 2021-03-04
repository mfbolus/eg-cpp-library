# Model Definition
In this library, linear regression models take the following form:

{{< katex display >}}
\mathbf{y}_t = \mathbf{C} \mathbf{x}_{t} + \mathbf{d}
{{< /katex >}}

{{< katex display >}}
\mathbf{z}_t \sim \mathcal{N}\left(\mathbf{y}_t , \mathbf{R} \right)
{{< /katex >}}

where {{<katex>}} \mathbf{x}_{t} {{</katex>}}, {{<katex>}} \mathbf{y}_{t} {{</katex>}}, and {{<katex>}} \mathbf{z}_{t} {{</katex>}} the input, output, and measurement, respectively; {{<katex>}} \mathbf{C} {{</katex>}} is the output matrix; {{<katex>}} \mathbf{d} {{</katex>}} is the output bias; and {{<katex>}} \mathbf{R} {{</katex>}} is the covariance of the assumed Gaussian measurement noise.
