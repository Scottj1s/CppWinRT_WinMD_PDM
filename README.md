# CppWinRT WinMD Verification

This project demonstrates standalone build logic to ensure consistent projections in C++/WinRT solutions.

This build logic generates #pragma detect_mismatch (PDM) entries for each winmd referenced in creating a project's 
C++/WinRT projection. At link time, if the same winmd filename has two different PDM hash values, the build fails.
This ensures that inconsistent ABI definitions cannot be combined into a single module, which could occur with
different versions of the same dependency (e.g., Windows App SDK) or with different 'flavors' of the same 
dependency (e.g., WinUI2 and WinUI3). A dummy IDL definition is used to support static libraries, enforcing 
linkage to PDMs via the projection header. This way, IJW for all scenarios. Otherwise, each static library would 
have to #include the generated PDMs in common logic (e.g., pch.obj) to ensure linkage.

The potential exists for false positive build breaks, so this behavior should be opt in. For example, exact hash
equivalence means that minor non-ABI-breaking changes to metadata will break the build. It's also possible for 
metadata merging to result in two winmds with the same name (namespace) but different levels of nested content.
Finally, Windows SDK reference metadata must also be taken into account, so all projects must use the same 
version of the Windows SDK, or PDMs will break the build. One scenario that's not addressed is using two
versions of the same metadata in a single project. This isn't possible, as mdmerge would first fail out with 
duplicate type defintiions.
