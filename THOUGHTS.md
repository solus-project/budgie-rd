## Thought tracking

This document is here purely so I can condense my thoughts as and when I have
them and have something to refer back to later :P

### Execution shell

As opposed to a traditional "desktop shell", budgie-rd will primarily provide
an execution shell to load in services, UI providers and the applications.
This will be somewhat like a "normal" session except it will be entirely
plugin based and provide a framework for an implemented UI provider to run.

### Service driven

Core services will be plugin based, providing data, information and system
monitoring as part of the execution shell for the UI provider. Candidates
would include notifications, power, devices, etc. Specifically these will
not be UI widgets, they will instead abstract the system and session into
something a UI can **use**. Other examples might include XDG portal implementations.

### UI provider

The default UI shell will also be a plugin that is loaded within the execution
shell to leverage the services of the framework to provide the UI seen by
and interacted with by users. Our scope is to initially provide the default
"Budgie Desktop" shell as the out-of-the-box experience.

Later on this can be extended to other use cases such as OEM/first-run and installation
session UIs, by making everything pluggable. Instead of having to hack together
custom XSession scripts it will be possible to cherry-pick the required components
and build a first class experience.

### Thread safety

One of the larger issues with Budgie 10 was the lack of any kind of thread
safety, such as applets using libnotify to send a notification to the freedesktop
notifications service. Unfortunately this was provided BY the same process, and
would lead to dead lock.

Instead we should expose a kind of PluginRegistry where we can talk to various
system interfaces (see: Service driven) and allow messaging via these components.
Additionally sensitive components like the notification server should also be
thread-safe to eliminate potential future dead-lock situations.

### Pluggable

Everything should be pluggable. Importantly, however, we should expose all of
our own rich widgets and APIs so that others can trivially extend Budgie to
be theirs.
