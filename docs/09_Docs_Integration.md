---
layout: default
title: "09. RoveSoDocs Hub Integration Playbook"
---

# Chapter 09: RoveSoDocs Hub Integration Playbook

This chapter outlines the exact integration procedure that connects the **RoveComm Protocol Guide** to MRDT's centralized documentation hub at [docs.themrdt.org](https://docs.themrdt.org/). 

By following the dual-docset architecture pioneered by the Autonomy Software documentation team (Chapter 16 of the Autonomy Binder), the high-level **RoveComm Protocol Guide (Jekyll)** is deployed alongside the low-level **RoveComm C++ API Reference (Doxygen)** without path conflicts or routing collisions.

---

## 1. Dual-Docset Subpath Convention

On `docs.themrdt.org`, the `/rovecomm/` URL space is cleanly partitioned into two complementary docsets:

| Route Path | Generator / Engine | Source Repository & Branch | Purpose |
| :--- | :--- | :--- | :--- |
| **`/rovecomm/_j/`** | **Jekyll 3.10** | `MissouriMRDT/RoveComm_Base`<br>`(docs/rovecomm)` | **Protocol Architecture & Guide**: Conceptual manual, wire format, manifest ecosystem, multi-language guides, and tester tooling. |
| **`/rovecomm/_cpp/`** | **Doxygen** | `MissouriMRDT/RoveComm_CPP`<br>`(development)` | **C++ API Code Reference**: Low-level class inheritance, header documentation, struct definitions, and Doxygen call graphs. |

---

## 2. The 6-Step Integration Checklist

To wire `RoveComm_Base` into the central documentation pipeline:

### Step 1: Duplicate Jekyll Section in `RoveSoDocs/.github/workflows/deploy.yml`

In `MissouriMRDT/RoveSoDocs`, add a dedicated build job named `build_rovecomm_jekyll`:

```yaml
  # Build RoveComm Protocol Guide (Jekyll)
  build_rovecomm_jekyll:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout RoveComm Base (Docs Branch)
        uses: actions/checkout@v4
        with:
          repository: MissouriMRDT/RoveComm_Base
          ref: docs/rovecomm
          path: src/RoveComm_Base

      - name: Set up Ruby
        uses: ruby/setup-ruby@v1
        with:
          ruby-version: "3.1"
          bundler-cache: true
          working-directory: src/RoveComm_Base/docs

      - name: Build Jekyll Site
        run: |
          bundle exec jekyll build --baseurl "/rovecomm/_j"
        working-directory: src/RoveComm_Base/docs

      - name: Stage RoveComm Guide into out/
        run: |
          mkdir -p out/rovecomm/_j
          rsync -a src/RoveComm_Base/docs/_site/ out/rovecomm/_j/

      - name: Upload RoveComm Jekyll Artifact
        uses: actions/upload-artifact@v4
        with:
          name: rovecomm_jekyll_site
          path: out/rovecomm/_j/
          retention-days: 1
```

### Step 2: Merge Artifact in `assemble` Job

Add `build_rovecomm_jekyll` to the `needs:` array of the `assemble` job and download the artifact into `dist/rovecomm/_j/`:

```yaml
  assemble:
    needs:
      - build_vitepress
      - build_autonomy_jekyll
      - build_autonomy_doxygen
      - build_rovecomm_jekyll
      - build_rovecommcpp_doxygen
      - ...
```

### Step 3: Register SPA Fallback in `NotFoundContent.vue`

VitePress is a Single Page Application (SPA). To prevent client-side routing from intercepting direct hits or page reloads within `/rovecomm/_j/`:

In `.vitepress/theme/NotFoundContent.vue`, add `/rovecomm/_j/` to `refreshPrefixes`:

```javascript
const refreshPrefixes = [
  "/autonomy/_d/",
  "/autonomy/_j/",
  "/embedded/",
  "/rovecomm/_cpp/",
  "/rovecomm/_j/",
  "/RoveSoSimulator/_j/",
];
```

And add a quicklink to the 404 navigation recovery bar:

```html
<a href="/rovecomm/_j/" class="quicklink">RoveComm Guide</a>
```

### Step 4: Index Guide in MiniSearch Search Engine

In `tools/build-minisearch-index.mjs`, update `sectionFromUrl()` to index every HTML page in `/rovecomm/_j/` under the search facet `"RoveComm Protocol Guide"`:

```javascript
function sectionFromUrl(url) {
  if (url.startsWith("/autonomy/_d/")) return "Autonomy Software (Doxygen)";
  if (url.startsWith("/autonomy/_j/")) return "Autonomy Software (Binder)";
  if (url.startsWith("/rovecomm/_cpp/")) return "RoveComm C++ (Doxygen)";
  if (url.startsWith("/rovecomm/_j/")) return "RoveComm Protocol Guide";
  ...
}
```

### Step 5: Add Feature Card on Homepage (`index.md`)

In `RoveSoDocs/index.md`, add a feature card under `features:`:

```yaml
  - icon: ":satellite:"
    title: "RoveComm Protocol Guide"
    details: "Universal rover communications manual -- wire format specifications, manifest ecosystem, multi-language bindings, and diagnostic tester tooling."
    link: /rovecomm/_j/
    linkText: "Open RoveComm Guide"
```

### Step 6: Maintain Visual Grid Balance

Ensure the total number of feature cards on the homepage is a multiple of 3 (e.g., 6 or 9 cards) so that the 3-column desktop layout (`@media (min-width: 1400px)`) remains visually symmetrical.
