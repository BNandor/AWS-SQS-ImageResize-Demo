# AWS-SQS-ImageResize-Demo

## Build

Dependencies: CMake, OpenCV, AWS SDK

```bash
mkdir build
cd build && cmake .. -DBUILD_SHARED_LIBS=ON -DBUILD_DEPS=ON && make
```

## Run

```bash
./resize <aws-sqs-queue-url>
```

## Queue message format

```json
{
"width":300, 
"height":200, 
"image":"iVBORw0KGgoAAAANSUhEUgAAAGQAAAAzCAYAAAEWbp2NAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAAIdUAACHVAQSctJ0AAA3rSURBVGhD7ZsLlBxVmcc7wILrA0UElvUcIy5PV8+C4OJZkKhEjSyiQmYJJCEZyUwyMz090++q7q73u269q7r6ORkmiUGye9hVkN0j2ZcRl

--- base64 encoded image

+gwXqd1LPEAPNY3zJsl0ZqS2EpDqoNoqRpj68vF79UM82rqpbycM027x923cGqYdhqAfxi8ecSjb6lzD6sB242AtscyfgCrAVsSbtmrW3/1eF/enhBhq96PUG3/nEqIWzN9RLPFKLsU8Fvj9Tt4j+ZjHYouO7RbFBYfc2+Bn1tHPeV9A/jffmDAsbCVWHTW5QR1Onnw+VeyJ0U9FpP+oPwfHiU2JJcRRzI90ivBD2xN+paveViYLXoawZjcWC47lY6hp3SDSgrBJa6tbr7ybJp3gQXUyF5QuDKFPgJHxirXGEKymMGFRSiwB/WKlfWNFf1ZL1WM4tXBYefyA2b8rEiRo+sWRJv0ClutGxYVd+XzkNZpwXz4JsAbyzy/19Q0vUPG4KkZ6PEm9GV+CExKz8VPJwcfBPRIW3eKeqmf4VSUJRCjHk+F+WChyP+RiX4hyxe9Kqm2jVcMlvaojanGDiLOlJ1L/9WzfnLmVw63aZNmzannEjk/wBv2VvBzNJiWAAAAABJRU5ErkJggg=="
}
```