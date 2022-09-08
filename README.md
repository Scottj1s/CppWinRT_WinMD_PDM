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

Without any changes, this project will fail at build time with a series of errors like this:

```2>StaticLibrary1.lib(VerifyMetadata.obj) : error LNK2038: mismatch detected for 'Microsoft.Foundation.winmd hash': value 'C9E5609228E5C5ADC6C515554EBFFA2FE2AECD48AC52F3E604FEF79F9A5BEEA7' doesn't match value '7EF87E91971BAD5DC14F904475704DB4C480E39BE2F55416319C36FAB2A1E0C5' in VerifyMetadata.obj```

If StaticLibrary1 is updated from Windows App SDK 1.1.3 to 1.1.4, to match the app project, the build succeeds.
