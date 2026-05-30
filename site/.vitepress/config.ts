import { defineConfig } from "vitepress";

// ── C++ standards ────────────────────────────────────────────────────────────
const STANDARDS = [
  { id: "cpp98", label: "C++98", dir: "C++98", accent: "#F59E0B", core: 52,  stl: 161, year: 1998, codename: "The Foundation"    },
  { id: "cpp03", label: "C++03", dir: "C++03", accent: "#94A3B8", core: 3,   stl: 2,   year: 2003, codename: "The Refinement"    },
  { id: "cpp11", label: "C++11", dir: "C++11", accent: "#06B6D4", core: 53,  stl: 160, year: 2011, codename: "The Modern Era"    },
  { id: "cpp14", label: "C++14", dir: "C++14", accent: "#10B981", core: 10,  stl: 13,  year: 2014, codename: "The Polish"        },
  { id: "cpp17", label: "C++17", dir: "C++17", accent: "#3B82F6", core: 19,  stl: 78,  year: 2017, codename: "The Pragmatic"     },
  { id: "cpp20", label: "C++20", dir: "C++20", accent: "#8B5CF6", core: 39,  stl: 245, year: 2020, codename: "The Big Four"      },
  { id: "cpp23", label: "C++23", dir: "C++23", accent: "#EC4899", core: 13,  stl: 76,  year: 2023, codename: "The Refinement II" },
  { id: "cpp26", label: "C++26", dir: "C++26", accent: "#F43F5E", core: 11,  stl: 33,  year: 2026, codename: "The Future"        },
];

// ── Go topics ────────────────────────────────────────────────────────────────
const GO_TOPICS = [
  { id: "go-history",  label: "History & Evolution", link: "/go/history",  icon: "📜" },
  { id: "go-core",     label: "Core Language",        link: "/go/core",     icon: "🔧" },
  { id: "go-conc",     label: "Concurrency",          link: "/go/concurrency", icon: "⚡" },
  { id: "go-stdlib",   label: "Standard Library",     link: "/go/stdlib",   icon: "📦" },
  { id: "go-advanced", label: "Advanced",             link: "/go/advanced", icon: "🚀" },
];

// ── Python topics ─────────────────────────────────────────────────────────────
const PYTHON_TOPICS = [
  { id: "py-history",  label: "History & Evolution", link: "/python/history",          icon: "📜" },
  { id: "py-core",     label: "Core Language",        link: "/python/core",             icon: "🔧" },
  { id: "py-stdlib",   label: "Standard Library",     link: "/python/stdlib",           icon: "📦" },
  { id: "py-conc",     label: "Concurrency",          link: "/python/concurrency",      icon: "⚡" },
  { id: "py-advanced", label: "Advanced",             link: "/python/advanced",         icon: "🚀" },
];

// ── Sidebars ─────────────────────────────────────────────────────────────────
const cppSidebar = STANDARDS.map((s) => ({
  text: `${s.label} · ${s.core + s.stl} concepts`,
  collapsed: true,
  items: [
    { text: "Overview",                     link: `/${s.id}/`    },
    { text: `Core Language (${s.core})`,    link: `/${s.id}/core` },
    { text: `STL & Library (${s.stl})`,     link: `/${s.id}/stl`  },
  ],
}));

const goSidebar = [
  {
    text: "Go — Multi-Paradigm Language",
    collapsed: false,
    items: GO_TOPICS.map((t) => ({ text: `${t.icon} ${t.label}`, link: t.link })),
  },
];

const pythonSidebar = [
  {
    text: "Python — Batteries Included",
    collapsed: false,
    items: PYTHON_TOPICS.map((t) => ({ text: `${t.icon} ${t.label}`, link: t.link })),
  },
];

export default defineConfig({
  title: "CodeNebula",
  description: "C++, Go & Python concepts with real-world scenarios and runnable examples — multiple languages, one reference.",
  base: "/CodeNebula/",
  srcDir: ".",
  outDir: ".vitepress/dist",
  ignoreDeadLinks: true,

  head: [
    ["link", { rel: "icon", type: "image/svg+xml", href: "/CodeNebula/favicon.svg" }],
    ["meta", { name: "theme-color", content: "#00599C" }],
    ["meta", { property: "og:title", content: "CodeNebula — Multi-Language Reference" }],
    ["meta", { property: "og:description", content: "C++ & Go concepts with real-world scenarios and runnable examples." }],
  ],

  themeConfig: {
    logo: { light: "/logo-light.svg", dark: "/logo-dark.svg", alt: "CodeNebula" },
    siteTitle: "CodeNebula",

    nav: [
      { text: "Home", link: "/" },
      {
        text: "C++",
        items: [
          { text: "All C++ Concepts", link: "/concepts" },
          { text: "─────────────", link: "/" },
          ...STANDARDS.map((s) => ({
            text: `${s.label} — ${s.codename}`,
            link: `/${s.id}/`,
          })),
        ],
      },
      {
        text: "Go",
        items: GO_TOPICS.map((t) => ({ text: `${t.icon} ${t.label}`, link: t.link })),
      },
      {
        text: "Python",
        items: [
          { text: "🐍 Python Overview", link: "/python/" },
          { text: "─────────────", link: "/" },
          ...PYTHON_TOPICS.map((t) => ({ text: `${t.icon} ${t.label}`, link: t.link })),
        ],
      },
      {
        text: "GitHub",
        link: "https://github.com/pruthvipanchal/CodeNebula",
        target: "_blank",
      },
    ],

    sidebar: {
      "/cpp":     cppSidebar,
      "/go/":     goSidebar,
      "/go":      goSidebar,
      "/python/": pythonSidebar,
      "/python":  pythonSidebar,
      // Map each C++ standard prefix to the C++ sidebar
      ...Object.fromEntries(STANDARDS.map((s) => [`/${s.id}/`, cppSidebar])),
      "/concepts": cppSidebar,
    },

    outline: { level: [2, 3], label: "On this page" },

    search: { provider: "local" },

    socialLinks: [
      { icon: "github", link: "https://github.com/pruthvipanchal/CodeNebula" },
    ],

    footer: {
      message: "Released under the MIT License.",
      copyright: "Copyright © 2026-present Pruthvi Panchal · CodeNebula",
    },

    editLink: {
      pattern: "https://github.com/pruthvipanchal/CodeNebula/edit/main/docs/:path",
      text: "Edit this page on GitHub",
    },

    lastUpdated: { text: "Updated at", formatOptions: { dateStyle: "short" } },
  },

  markdown: {
    theme: { light: "github-light", dark: "github-dark" },
    anchor: {
      slugify: (str: string) =>
        str
          .toLowerCase()
          .replace(/[^\w\s-]/g, "")
          .replace(/\s/g, "-"),
    },
    config(md) {
      // Insert blank lines before **Label**: fields so each renders as its own paragraph.
      const _render = md.render.bind(md);
      (md as unknown as { render: (src: string, env?: unknown) => string }).render =
        (src: string, env?: unknown): string => {
          const processed = src.replace(
            /\n(?!\n)(\*\*(?:Explanation|Real-World Scenario|Snippet|Example|Compile[^*]*)\*\*\s*:)/gi,
            "\n\n$1"
          );
          return _render(processed, env);
        };

      // Escape C++ template angle-brackets so Vue doesn't treat them as component tags.
      md.core.ruler.push("escape-cpp-templates", (state) => {
        for (const token of state.tokens) {
          if (token.type === "inline" && token.children) {
            for (const child of token.children) {
              if (child.type === "text") {
                child.content = child.content.replace(
                  /<([A-Za-z_][A-Za-z0-9_,\s*&:<>]*?)>/g,
                  "&lt;$1&gt;"
                );
              } else if (child.type === "html_inline") {
                if (/^<\/?[A-Za-z_][A-Za-z0-9_,\s*&:<>]*\/?>$/.test(child.content)) {
                  child.type = "text";
                  child.content = child.content
                    .replace(/</g, "&lt;")
                    .replace(/>/g, "&gt;");
                }
              }
            }
          }
        }
      });

      md.core.ruler.push("rewrite-links", (state) => {
        for (const token of state.tokens) {
          if (token.type === "inline" && token.children) {
            for (const child of token.children) {
              if (child.type === "link_open") {
                const hrefAttr = child.attrs?.find(([k]) => k === "href");
                if (hrefAttr && typeof hrefAttr[1] === "string") {
                  const href = hrefAttr[1] as string;

                  // Rewrite doc-relative links in master.md: C++98/core_language.md → /cpp98/core
                  const docLink = href.match(/(?:\.\/)?C\+\+(\d+)\/(core_language|stl_concepts)\.md$/);
                  if (docLink) {
                    const type = docLink[2] === "core_language" ? "core" : "stl";
                    hrefAttr[1] = `/cpp${docLink[1]}/${type}`;
                  }

                  // Rewrite C++ example links → GitHub blob URLs (now under examples/cpp/)
                  const cppExample = href.match(/\.\.\/\.\.\/examples\/(C\+\+\d+)\/(.+\.cpp)/);
                  if (cppExample) {
                    hrefAttr[1] = `https://github.com/pruthvipanchal/CodeNebula/blob/main/examples/cpp/${cppExample[1]}/${cppExample[2]}`;
                    const targetAttr = child.attrs?.find(([k]) => k === "target");
                    if (targetAttr) {
                      targetAttr[1] = "_blank";
                    } else {
                      child.attrs = child.attrs || [];
                      child.attrs.push(["target", "_blank"]);
                      child.attrs.push(["rel", "noopener noreferrer"]);
                    }
                  }

                  // Rewrite Go example links → GitHub blob URLs (examples/go/{topic}/file.go)
                  const goExample = href.match(/\.\.\/\.\.\/examples\/go\/([^/]+)\/(.+\.go)/);
                  if (goExample) {
                    hrefAttr[1] = `https://github.com/pruthvipanchal/CodeNebula/blob/main/examples/go/${goExample[1]}/${goExample[2]}`;
                    const targetAttr = child.attrs?.find(([k]) => k === "target");
                    if (targetAttr) {
                      targetAttr[1] = "_blank";
                    } else {
                      child.attrs = child.attrs || [];
                      child.attrs.push(["target", "_blank"]);
                      child.attrs.push(["rel", "noopener noreferrer"]);
                    }
                  }

                  // Rewrite Python example links → GitHub blob URLs (examples/python/{topic}/file.py)
                  const pyExample = href.match(/\.\.\/\.\.\/examples\/python\/([^/]+)\/(.+\.py)/);
                  if (pyExample) {
                    hrefAttr[1] = `https://github.com/pruthvipanchal/CodeNebula/blob/main/examples/python/${pyExample[1]}/${pyExample[2]}`;
                    const targetAttr = child.attrs?.find(([k]) => k === "target");
                    if (targetAttr) {
                      targetAttr[1] = "_blank";
                    } else {
                      child.attrs = child.attrs || [];
                      child.attrs.push(["target", "_blank"]);
                      child.attrs.push(["rel", "noopener noreferrer"]);
                    }
                  }
                }
              }
            }
          }
        }
      });
    },
  },
});
