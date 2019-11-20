# Contributing to sc-implant
`sc-implant`, is a project where reliability is a high priority, and therefore must be developed with a  stringent quality control process. The goal of this document is to act as a guide when making or reviewing contributions to this project.

## Submitting issues
### Feature requests
When submitting feature requests, please identify whether your request is to extend existing functionality or add an additional feature to the project. 

**For extending existing functionality:** please identify the module you want additional functionality to be added to. 

**For new features:** please suggest ways in which your feature may be laid out so as to fit in with the existing project structure.

Provide as much detail as possible about how you would like your feature request to look, but be aware that other contributors will need to agree for your feature to be implemented and they may suggest alterations. 

### Bug Reports
Please include any error/debug messages or crash logs that are relevant. 

Describe what behaviour you are seeing and how this differs from the behaviour you expect. 

Where possible, please provide simple reproduction instructions. Ideally, you should be able to find the simplest set of circumstances under which the bug occurs. 

In order to get your bug identified and resolved as quickly as possible, please try to make yourself available to answer questions by whoever is attempting to triage and resolve the issue. 

## Making changes
`sc-implant`, as a release-based project, is developed using [Gitflow Workflow](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow). 

### Documentation and testing
Noteworthy changes should have an accompanying addition to the changelog. 

Additionally, to maintain good documentation and CI/CD of `sc-implant`, in-code documentation and tests should be included with any feature additions.  
### Commit
Ensure that commits are made under your name and University of New South Wales zID email account (zid@unsw.edu.au). You can ensure that this is the case by running the following commands from the root directory of the project:
```console
$ git config --local user.name "John Smith"
$ git config --local user.email "z5123456@unsw.edu.au"
```
To confirm, run `git config --local --all` to print the current configuration.
When writing Git commits, use a strict style using [this post](https://chris.beams.io/posts/git-commit/) as a style guide.

### Merge Requests
When making a merge request, ensure that it is a *complete* feature that does not break the branch. If it does break the branch but there are extenuating circumstances justifying it, please detail that in the merge request clearly. Before a merge request is merged, **there must be a thorough and complete code review by another member of the team**. Once approved by the reviewer, it should then be merged by a third member if the changes are in-line with the goals of the project.
#### Choosing a Reviewer
If you are modifying existing code it is ideal to use `git blame`, identify the original contributor, and then flag them as the reviewer for the merge request. If you are contributing new code use your discretion for you want to review the contribution. 

## Completing a Review
When completing a review ensure that the merge request does not introduce breaking changes or technical debt. You are the main line of defense when it comes to preventing future problems in the code base. From a social perspective, try to provide constructive criticism and provide a thorough explanation for why something might not be up to your standards if that's the case.

At a minimum, you should: 
1. Look through the code to see if you can quickly identify out any mistakes. Pointing these out early can help the developer rectify the issues while you review the rest of the code. 
2. Restart vagrant to ensure you are starting from a clean environment. 
3. Build the project, and ensure it still operates as expected. 
4. Look through the code to find edge cases and branch conditions.
5. Test the changes that have been implemented, ensuring your actions have executed as much of the code as possible.

Once you're happy with the change, comment on the merge request giving your approval and:
 - If you are the first reviewer, assign a second reviewer.
 - If you are the second reviewer, either merge the request yourself, ensuring that the commit message is appropriate and the source branch is removed; or ask the contributer that opened the request to merge. 

## Code Style
The Linux kernel style guide, found [here](https://www.kernel.org/doc/html/v4.10/process/coding-style.html), should be used to format all code contributions. This can be done using `clang-tidy` prior to making a merge request.
