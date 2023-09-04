# OSN 2023 Problem Repository

Problem repository of **OSN 2023** (also known internationally as
**TOKI Indonesian NOI Open Contest 2023**).

## Problems

| Alias | Slug                  | Title (id)           | Title (en)          | Type  |
| ----- | --------------------- | -------------------- | ------------------- | ----- |
| 1A    | `osn-2023-pertahanan` | Pertahanan Bogor     | Bogor Defence       | batch |
| 1B    | `osn-2023-semut`      | Semut Kesepian       | Lonely Ants         | batch |
| 1C    | `osn-2023-hujan`      | Kota Hujan           | Rain City           | batch |
| 2A    | `osn-2023-tv`         | Kelap-Kelip Televisi | Television Flickers | batch |
| 2B    | `osn-2023-talas`      | Berbagi Lapis Talas  | Sharing Lapis Talas | batch |
| 2C    | `osn-2023-pengiriman` | Pengiriman Satu Hari | One-Day Delivery    | batch |

## Credits

| Slug                  | Problem Author(s)                         |
| --------------------- | ----------------------------------------- |
| `osn-2023-pertahanan` | Pikatan Arya Bramajati                    |
| `osn-2023-semut`      | Pikatan Arya Bramajati                    |
| `osn-2023-hujan`      | Maximilliano Utomo Quok                   |
| `osn-2023-tv`         | Prabowo Djonatan                          |
| `osn-2023-talas`      | Muhammad Ayaz Dzulfikar, Prabowo Djonatan |
| `osn-2023-pengiriman` | Rama Aryasuta Pangestu                    |

## Upsolving

The problem statements and upsolving are available
[on TLX](https://tlx.toki.id/problems/osn-2023).

The editorial can also be found on the same link

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

Test case generator using [tcframe](http://tcframe.toki.id/en/stable/) 1.6.0.

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

## License

All tasks and materials are published under the [Creative Commons Attribution
(CC-BY)](https://github.com/ia-toki/osn-2023/blob/master/LICENSE) License.