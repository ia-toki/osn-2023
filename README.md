# OSN 2023 Problem Repository

## Problem slugs

* `osn-2023-pertahanan`
* `osn-2023-semut`
* `osn-2023-hujan`
* `osn-2023-tv`
* `osn-2023-talas`
* `osn-2023-pengiriman`

## Problem Structure Repository

Each problem contains a problem directory root (e.g. `osn-2023-pertahanan/`).
A problem directory root contains the following files and directories:

* ID problem description (`description-id.html`)
* EN problem description (`description-en.html`)
* Model solution (`solution.cpp`)
* Subtasks solution (`solution-{subtask_number}.cpp`)
* Test case generator (`spec.cpp`)
* Configuration file (`config.json`)
* Alternative solutions (`solution_{author}_{verdict}_{solution-name}.cpp`)
* Render directory (`render/`)
* Helper directory (`helper/`)
* Communicator (`communicator.cpp`)
* Output validator (`scorer.cpp`)

### ID problem description

Problem description in Bahasa Indonesia.
The HTML file uses [Katex](https://katex.org/) syntax to render the math equations.

### EN problem description

Problem description in English language.

### Model solution

The solution used to generate the test cases.

### Subtasks solution

Solutions that are used for the purpose of testing the subtasks.

### Test case generator

Test case generator using [tcframe](http://tcframe.toki.id/en/stable/) v1.6.0.

### Configuration file

Contains a JSON object that may help with the automation to choose the correct settings in online judges.
Possible configs in this file:

* `time_limit` (number in ms)
* `memory_limit` (number in kB)
* `samples` (a list of lists that maps a sample to its subtasks)
* `test_groups` (a list of lists that maps test group to its subtasks)
* `points` (a list containing the points of each subtask)
* `interactive` (a boolean).

### Alternative solutions

Several alternative and wrong solutions for the purpose of testing.

### Render directory

Contains the assets that is used by the HTML description file.
Usually contains images.

### Helper directory

May contain scripts that help with problem preparation or the raw files of the assets in `render/`.

### Communicator

For communication in interactive problem using [tcframe format](https://tcframe.toki.id/en/stable/topic-guides/styles.html#communicator)

### Output validator

To validate solutions which do not use exact match (may contain multiple solutions or require precision handling) using [tcframe format](https://tcframe.toki.id/en/stable/topic-guides/styles.html#scorer).
