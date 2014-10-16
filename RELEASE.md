#BitBang Framework Release Procedure

1. Prepare the source code:

    * Update VERSION in source
    * Update changelog
    * Commit to repository
    * Create tag for release version in repository

2. Generate new API documentation

3. Create source release
	* Get zip archive from repository (tagged version)

4. Build binaries

    4.1. Build Mac binary release

    * Clone from git to a fresh directory
    * Build libraries using XCode with *Release* configuration
    * Create release directory named bitbang_xx.yy_mac_universal
    * Copy files to new directory
    * Create zip archive

    4.2. Build Windows binary release

    4.3. Build Linux binary release

5. Upload releases to sourceforge

6. Announce release:

    * Web site news
    * Sourceforge
    * twitter
